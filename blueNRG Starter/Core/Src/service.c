#include "bluenrg_conf.h"
#include "bluenrg1_types.h"
#include "bluenrg1_gap.h"
#include "bluenrg1_aci.h"
#include "bluenrg1_hci_le.h"

#include "service.h"

const uint8_t SERVICE_UUID[16] 	= {0x66, 0x9a, 0x0c, 0x20, 0x00, 0x08, 0x96, 0x9e, 0xe2, 0x11, 0x9e, 0xb1, 0xe0, 0xf2, 0x73, 0xd9};
const uint8_t CHAR_UUID[16]		= {0x66, 0x9a, 0x0c, 0x20, 0x00, 0x08, 0x96, 0x9e, 0xe2, 0x11, 0x9e, 0xb1, 0xe1, 0xf2, 0x73, 0xd9};
uint16_t service_handle;

tBleStatus add_simple_service() {
	tBleStatus ret;
	Service_UUID_t service_uuid;
	BLUENRG_memcpy(service_uuid.Service_UUID_128, SERVICE_UUID, 16);

	// add service to GATT
	ret = aci_gatt_add_service(
			UUID_TYPE_128, // Service_UUID_Type
			&service_uuid,
			PRIMARY_SERVICE, // Service_Type
			7, // Max_Attribute_Records
			&service_handle);

	return ret;
}
