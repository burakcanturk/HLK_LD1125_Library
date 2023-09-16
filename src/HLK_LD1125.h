#ifndef _HLK_LD1125_
#define _HLK_LD1125_

#define HLK_LD1125_BAUD 115200

//------------------------------------------------

#define occ_txt "occ,"
#define mov_txt "mov,"

//------------------------------------------------

#define conf_vals_len 10

#define get_all_str "get_all"
#define get_all_suc_str "received message: get_all\r"

//------------------------------------------------

#define save_str "save"
#define save_suc_str "received message: save\r"
#define save_suc2_str "all vars have been saved\r"

//------------------------------------------------

#include <Arduino.h>
#ifndef _BOARD_GENERIC_STM32F103C_H_
#include <SoftwareSerial.h>
#endif

class HLK_LD1125 {

  public:
#ifndef ESP32
#ifndef _BOARD_GENERIC_STM32F103C_H_
    HLK_LD1125(SoftwareSerial *ssUart);
#endif
#else
    HLK_LD1125(EspSoftwareSerial::UART *ssEspUart);
    HLK_LD1125(uint8_t rx, uint8_t tx, EspSoftwareSerial::UART *ssEspUart);
    HLK_LD1125(uint8_t rx, uint8_t tx, HardwareSerial *hsUart);
#endif
    HLK_LD1125(HardwareSerial *hsUart);
    HLK_LD1125(uint8_t rx, uint8_t tx);
    void begin();
    void read();
    String getDisType();
    float getOccDis();
    float getMovDis();
    float getOccStr();
    float getMovStr();
    void getAllSettings();
    float getRmax();
    uint16_t getMth1Mov();
    uint16_t getMth2Mov();
    uint16_t getMth3Mov();
    uint16_t getMth1Occ();
    uint16_t getMth2Occ();
    uint16_t getMth3Occ();
    uint16_t getTsOn();
    uint16_t getTsOff();
    bool getOutputMode();
    bool saveAllSettings();
    bool setRmax(float rmax); // 8.00
    bool setMth1Mov(uint16_t mth1_mov); // 80
    bool setMth2Mov(uint16_t mth2_mov); // 50
    bool setMth3Mov(uint16_t mth3_mov); // 20
    bool setMth1Occ(uint16_t mth1_occ); // 60
    bool setMth2Occ(uint16_t mth2_occ); // 55
    bool setMth3Occ(uint16_t mth3_occ); // 20
    bool setTsOn(uint16_t ts_on); // 60
    bool setTsOff(uint16_t ts_off); // 15
    bool setOutputMode(bool output_mode); // 0
    bool setTestMode(bool test_mode);

  private:

    bool is_soft;

#ifndef ESP32
#ifndef _BOARD_GENERIC_STM32F103C_H_
    SoftwareSerial *SS;
#endif
#else
    EspSoftwareSerial::UART *SS;
#endif
    HardwareSerial *HS;

    bool with_pins;
    bool with_ser;

    uint16_t rx_pin;
    uint16_t tx_pin;

    struct ld1125_datas {
      String dis_type;
      float occ_dis;
      float mov_dis;
      float occ_str;
      float mov_str;
    } ld1125_data;

    bool test_mode = false;

    struct ld1125_conf_datas {
      float rmax;
      uint16_t mth1_mov;
      uint16_t mth2_mov;
      uint16_t mth3_mov;
      uint16_t mth1_occ;
      uint16_t mth2_occ;
      uint16_t mth3_occ;
      uint16_t ts_on;
      uint16_t ts_off;
      bool output_mode;
    } ld1125_conf_data;
};

#endif
