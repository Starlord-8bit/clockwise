#pragma once

/**
 * CWMqtt.h — MQTT client for Clockwise Paradise
 *
 * Uses ESP-IDF's native mqtt/esp-mqtt component (no external library needed).
 *
 * Topics (prefix configurable, default "clockwise"):
 *
 * PUBLISH (state):
 *   <prefix>/state       — JSON: {clockface, brightness, nightMode, totalDays}
 *   <prefix>/availability — "online" / "offline" (LWT)
 *
 * SUBSCRIBE (commands):
 *   <prefix>/set/brightness   — 0-255
 *   <prefix>/set/nightMode    — 0/1/2
 *   <prefix>/set/clockface    — 1-7 (face number)
 *   <prefix>/restart          — any payload
 */

#include <Arduino.h>
#include <CWPreferences.h>
#include <StatusController.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "mqtt_client.h"
#ifdef __cplusplus
}
#endif

#define MQTT_STATE_INTERVAL_MS 30000  // publish state every 30 seconds

class CWMqtt {
public:
    static CWMqtt* getInstance() {
        static CWMqtt instance;
        return &instance;
    }

    void begin() {
        auto* p = ClockwiseParams::getInstance();
        if (!p->mqttEnabled || p->mqttBroker.isEmpty()) return;

        String broker_uri = "mqtt://" + p->mqttBroker + ":" + String(p->mqttPort);
        String lwt_topic  = p->mqttPrefix + "/availability";

        esp_mqtt_client_config_t cfg = {};
        cfg.broker.address.uri       = broker_uri.c_str();
        cfg.credentials.username     = p->mqttUser.isEmpty()     ? nullptr : p->mqttUser.c_str();
        cfg.credentials.authentication.password = p->mqttPass.isEmpty() ? nullptr : p->mqttPass.c_str();
        cfg.session.last_will.topic  = lwt_topic.c_str();
        cfg.session.last_will.msg    = "offline";
        cfg.session.last_will.qos    = 1;
        cfg.session.last_will.retain = 1;

        _client = esp_mqtt_client_init(&cfg);
        esp_mqtt_client_register_event(_client, MQTT_EVENT_ANY, _mqtt_event_handler, this);
        esp_mqtt_client_start(_client);

        Serial.printf("[MQTT] Connecting to %s\n", broker_uri.c_str());
        _enabled = true;
    }

    void loop() {
        if (!_enabled || !_connected) return;
        if (millis() - _lastPublish > MQTT_STATE_INTERVAL_MS) {
            publishState();
            _lastPublish = millis();
        }
    }

    void publishState() {
        if (!_enabled || !_connected) return;
        auto* p = ClockwiseParams::getInstance();
        String topic   = p->mqttPrefix + "/state";
        String payload = "{\"clockface\":" + String(p->autoChange) +
                         ",\"brightness\":" + String(p->displayBright) +
                         ",\"nightMode\":"  + String(p->nightMode) +
                         ",\"totalDays\":"  + String(p->totalDays) + "}";
        esp_mqtt_client_publish(_client, topic.c_str(), payload.c_str(), 0, 1, 0);
    }

    bool isConnected() const { return _connected; }

private:
    esp_mqtt_client_handle_t _client = nullptr;
    bool _enabled   = false;
    bool _connected = false;
    long _lastPublish = 0;

    // Command handler — called from MQTT event for incoming messages
    void handleCommand(const String& topic, const String& payload) {
        auto* p = ClockwiseParams::getInstance();
        String prefix = p->mqttPrefix;

        if (topic == prefix + "/set/brightness") {
            int val = payload.toInt();
            if (val >= 0 && val <= 255) {
                p->displayBright = val;
                p->save();
                // brightness applied in main loop via automaticBrightControl
            }
        } else if (topic == prefix + "/set/nightMode") {
            int val = payload.toInt();
            if (val >= 0 && val <= 2) {
                p->nightMode = val;
                p->save();
            }
        } else if (topic == prefix + "/set/clockface") {
            // Stub — full effect requires dispatcher merge
            int val = payload.toInt();
            Serial.printf("[MQTT] clockface command: %d (requires dispatcher)\n", val);
        } else if (topic == prefix + "/restart") {
            Serial.println("[MQTT] Restart command received");
            StatusController::getInstance()->forceRestart();
        }

        publishState();  // echo state after any command
    }

    static void _mqtt_event_handler(void* handler_args, esp_event_base_t base,
                                    int32_t event_id, void* event_data)
    {
        CWMqtt* self = static_cast<CWMqtt*>(handler_args);
        esp_mqtt_event_handle_t event = static_cast<esp_mqtt_event_handle_t>(event_data);

        switch ((esp_mqtt_event_id_t)event_id) {
            case MQTT_EVENT_CONNECTED: {
                self->_connected = true;
                Serial.println("[MQTT] Connected");
                // Publish online availability
                auto* p = ClockwiseParams::getInstance();
                String avail = p->mqttPrefix + "/availability";
                esp_mqtt_client_publish(self->_client, avail.c_str(), "online", 0, 1, 1);
                // Subscribe to command topics
                String prefix = p->mqttPrefix;
                esp_mqtt_client_subscribe(self->_client, (prefix + "/set/brightness").c_str(), 1);
                esp_mqtt_client_subscribe(self->_client, (prefix + "/set/nightMode").c_str(), 1);
                esp_mqtt_client_subscribe(self->_client, (prefix + "/set/clockface").c_str(), 1);
                esp_mqtt_client_subscribe(self->_client, (prefix + "/restart").c_str(), 1);
                self->publishState();
                break;
            }
            case MQTT_EVENT_DISCONNECTED:
                self->_connected = false;
                Serial.println("[MQTT] Disconnected");
                break;
            case MQTT_EVENT_DATA: {
                String topic(event->topic, event->topic_len);
                String payload(event->data, event->data_len);
                self->handleCommand(topic, payload);
                break;
            }
            default:
                break;
        }
    }
};
