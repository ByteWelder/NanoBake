#include "wifi.h"

#include "app_manifest.h"
#include "esp_lvgl_port.h"
#include "furi_core.h"
#include "wifi_state_updating.h"

// Forward declarations
static void wifi_event_callback(const void* message, void* context);

static Wifi* wifi_alloc() {
    Wifi* wifi = malloc(sizeof(Wifi));

    FuriPubSub* wifi_pubsub = wifi_get_pubsub();
    wifi->wifi_subscription = furi_pubsub_subscribe(wifi_pubsub, &wifi_event_callback, wifi);
    wifi->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    wifi->state = (WifiState) {
        .scanning = false,
        .radio_state = wifi_get_enabled() ? WIFI_RADIO_ON : WIFI_RADIO_OFF
    };
    wifi->view = (WifiView) {
        .scanning_spinner = NULL
    };

    return wifi;
}

static void wifi_free(Wifi* wifi) {
    FuriPubSub* wifi_pubsub = wifi_get_pubsub();
    furi_pubsub_unsubscribe(wifi_pubsub, wifi->wifi_subscription);
    furi_mutex_free(wifi->mutex);

    free(wifi);
}

void wifi_lock(Wifi* wifi) {
    furi_assert(wifi);
    furi_assert(wifi->mutex);
    furi_mutex_acquire(wifi->mutex, FuriWaitForever);
}

void wifi_unlock(Wifi* wifi) {
    furi_assert(wifi);
    furi_assert(wifi->mutex);
    furi_mutex_release(wifi->mutex);
}

static void wifi_event_callback(const void* message, void* context) {
    const WifiEvent* event = (const WifiEvent*)message;
    Wifi* wifi = (Wifi*)context;
    switch (event->type) {
        case WifiEventTypeScanStarted:
            wifi_state_set_scanning(wifi, true);
            break;
        case WifiEventTypeScanFinished:
            wifi_state_set_scanning(wifi, false);
            break;
        case WifiEventTypeRadioStateOn:
            wifi_state_set_radio_state(wifi, WIFI_RADIO_ON);
            wifi_scan();
            break;
        case WifiEventTypeRadioStateOnPending:
            wifi_state_set_radio_state(wifi, WIFI_RADIO_ON_PENDING);
            break;
        case WifiEventTypeRadioStateOff:
            wifi_state_set_radio_state(wifi, WIFI_RADIO_OFF);
            break;
        case WifiEventTypeRadioStateOffPending:
            wifi_state_set_radio_state(wifi, WIFI_RADIO_OFF_PENDING);
            break;
    }
}

static void app_show(Context* context, lv_obj_t* parent) {
    Wifi* wifi = (Wifi*)context->data;

    wifi_lock(wifi);
    wifi_view_create(&wifi->view, parent);
    wifi_view_update(&wifi->view, &wifi->state);
    wifi_unlock(wifi);

    if (wifi_get_enabled()) {
        wifi_scan();
    }
}

static void app_hide(Context* context) {
    Wifi* wifi = (Wifi*)context->data;

    wifi_lock(wifi);
    wifi_view_clear(&wifi->view);
    wifi_unlock(wifi);
}

static void app_start(Context* context) {
    Wifi* wifi = wifi_alloc();
    context->data = wifi;
}

static void app_stop(Context* context) {
    Wifi* wifi = context->data;
    furi_assert(wifi != NULL);
    wifi_free(wifi);
    context->data = NULL;
}

AppManifest wifi_app = {
    .id = "wifi",
    .name = "Wi-Fi",
    .icon = NULL,
    .type = AppTypeSystem,
    .on_start = &app_start,
    .on_stop = &app_stop,
    .on_show = &app_show,
    .on_hide = &app_hide
};