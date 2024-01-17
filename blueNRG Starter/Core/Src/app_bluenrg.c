#include <stdio.h>
#include "hci.h"
#include "bluenrg_conf.h"
#include "bluenrg1_types.h"
#include "bluenrg1_gap.h"
#include "bluenrg1_aci.h"
#include "bluenrg1_hci_le.h"

#include "app_bluenrg.h"
#include "service.h"

uint8_t PUBADDR[CONFIG_DATA_PUBADDR_LEN] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x6};

void bluenrg_init() {
	const char *device_name = "blueNRG2";
	uint8_t pubaddr[CONFIG_DATA_PUBADDR_LEN];
	BLUENRG_memcpy(pubaddr, PUBADDR, CONFIG_DATA_PUBADDR_LEN);
	uint16_t service_handle, dev_name_char_handle, appearance_char_handle;
	tBleStatus ret;

	// initialize HCI
	hci_init(NULL, NULL);

	// reset HCI
	hci_reset();
	HAL_Delay(100);

	// configure device address
	ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, pubaddr);
	if (ret != BLE_STATUS_SUCCESS) printf("aci_hal_write_config_data() failed.\n");

	// initialize GATT server
	ret = aci_gatt_init();
	if (ret != BLE_STATUS_SUCCESS) printf("aci_gatt_init() failed.\n");

	// initialize GAP service
	ret = aci_gap_init(
			GAP_PERIPHERAL_ROLE,
			0, // privacy_enabled
			10, // device_name_char_len
			&service_handle, &dev_name_char_handle, &appearance_char_handle);
	if (ret != BLE_STATUS_SUCCESS) printf("aci_gap_init() failed.\n");

	// update GAP characteristics
	ret = aci_gatt_update_char_value(service_handle, dev_name_char_handle,
			0, // Val_Offset
			strlen(device_name), // Char_Value_Length
			(uint8_t *)device_name // Char_Value
			);

	// add custom service
	ret = add_simple_service();
	if (ret != BLE_STATUS_SUCCESS) printf("add_simple_service() failed.\n");
}

void bluenrg_process() {
	uint8_t local_name[] = {AD_TYPE_COMPLETE_LOCAL_NAME, 'b', 'l', 'u', 'e', 'N', 'R', 'G', '2'};
	tBleStatus ret;

	// advertise
	ret = aci_gap_set_discoverable(
			ADV_IND, // Advertising_Type, undirected scannable and connectable
			0, // Advertising_Interval_Min
			0, // Advertising_Interval_Max
			PUBLIC_ADDR, // Own_Address_Type
			NO_WHITE_LIST_USE, // Advertising_Filter_Policy
			sizeof(local_name), // Local_Name_Length
			local_name, // Local_Name
			0, // Service_Uuid_length
			NULL, // Service_Uuid_List
			0, // Slave_Conn_Interval_Min
			0); // Slave_Conn_Interval_Max
	if (ret != BLE_STATUS_SUCCESS) printf("aci_gap_set_discoverable() failed.\n");
}
