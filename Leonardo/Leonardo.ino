#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(9);

void setup() {
    Serial.begin(115200);
    if(CAN0.begin(CAN_1000KBPS) == CAN_OK) Serial.print("can init ok!!\r\n");
    else Serial.println("not ok");
    pinMode(8, INPUT);

    //bitSet(txMask,0);
    //bitSet(txMask,1);
    CAN0.init_Mask(0, 0, 0x7F0);
    CAN0.init_Mask(1, 0, 0x7f0);
    CAN0.init_Filt(0, 0, 0x000);
    CAN0.init_Filt(1, 0, 0x010);
    CAN0.init_Filt(2, 0, 0x020);
    CAN0.init_Filt(3, 0, 0x030);
    CAN0.init_Filt(4, 0, 0x1f0);
    CAN0.init_Filt(5, 0, 0x2f0);

}

void loop() {
    //Remote.next();
    //Remote.clear();
    //delay(5000);

    if(!digitalRead(8))
    {
        CAN0.readMsgBuf(&len, rxBuf);
        rxId = CAN0.getCanId();
        Serial.print("ID: ");
        Serial.print(rxId, HEX);
        Serial.print("  Data: ");
        for(int i = 0; i<len; i++)
        {
            if(rxBuf[i] < 0x10)
            {
                Serial.print("0");
            }
            Serial.print(rxBuf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }

}
