#include "HLK_LD1125.h"

#ifndef ESP32

#ifndef _BOARD_GENERIC_STM32F103C_H_

HLK_LD1125::HLK_LD1125(SoftwareSerial *ssUart) {
  is_soft = true;
  with_pins = false;
  with_ser = true;
  SS = ssUart;
}

#endif

#else

HLK_LD1125::HLK_LD1125(EspSoftwareSerial::UART *ssEspUart) {
  is_soft = true;
  with_pins = false;
  with_ser = true;
  SS = ssEspUart;
}

HLK_LD1125::HLK_LD1125(uint8_t rx, uint8_t tx, EspSoftwareSerial::UART *ssEspUart) {
  is_soft = true;
  with_pins = true;
  with_ser = true;
  rx_pin = rx;
  tx_pin = tx;
  SS = ssEspUart;
}

HLK_LD1125::HLK_LD1125(uint8_t rx, uint8_t tx, HardwareSerial *hsUart) {
  is_soft = false;
  with_pins = true;
  with_ser = true;
  rx_pin = rx;
  tx_pin = tx;
  HS = hsUart;
}

#endif

HLK_LD1125::HLK_LD1125(HardwareSerial *hsUart) {
  is_soft = false;
  with_pins = false;
  with_ser = true;
  HS = hsUart;
}

HLK_LD1125::HLK_LD1125(uint8_t rx, uint8_t tx) {
  is_soft = true;
  with_pins = true;
  with_ser = false;
  rx_pin = rx;
  tx_pin = tx;
}

void HLK_LD1125::begin() {

#ifndef ESP32

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {
    if (not with_pins)
      SS->begin(HLK_LD1125_BAUD);
    else {
      SoftwareSerial ssUart(rx_pin, tx_pin);
      SS = &ssUart;
      SS->begin(HLK_LD1125_BAUD);
    }
  }

#endif

  if (not is_soft)
    HS->begin(HLK_LD1125_BAUD);

#else

  if (is_soft) {
    if (not with_pins)
      SS->begin(HLK_LD1125_BAUD);
    else {
      if (with_ser)
        SS->begin(HLK_LD1125_BAUD, EspSoftwareSerial::SWSERIAL_8N1, rx_pin, tx_pin);
      else {
        EspSoftwareSerial::UART ssUart(rx_pin, tx_pin);
        SS = &ssUart;
        SS->begin(HLK_LD1125_BAUD);
      }
    }
  }

  else {
    if (not with_pins)
      HS->begin(HLK_LD1125_BAUD);
    else
      HS->begin(HLK_LD1125_BAUD, SERIAL_8N1, rx_pin, tx_pin);
  }

#endif
}

void HLK_LD1125::read() {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String data_str = SS->readStringUntil('\n');

    String data_type = data_str.substring(0, data_str.indexOf(' '));

    if (data_type == ld1125_mov_txt) {

      ld1125_data.dis_type = "mov";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String data_vals_txt = data_vals.substring(0, data_vals.indexOf('='));

      if (data_vals_txt == "dis") {
        String data_vals_str = data_vals.substring(data_vals.indexOf('=') + 1, data_vals.length());
        ld1125_data.mov_dis = data_vals_str.toFloat();
      }

      if (test_mode) {

        String str_vals = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());

        String str_vals_txt = str_vals.substring(0, str_vals.indexOf('='));

        if (str_vals_txt == "str") {
          String str_vals_str = str_vals.substring(str_vals.indexOf('=') + 1, str_vals.length());
          ld1125_data.mov_str = str_vals_str.toFloat();
        }
      }
    }

    else if (data_type == ld1125_occ_txt) {

      ld1125_data.dis_type = "occ";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String data_vals_txt = data_vals.substring(0, data_vals.indexOf('='));

      if (data_vals_txt == "dis") {
        String data_vals_str = data_vals.substring(data_vals.indexOf('=') + 1, data_vals.length());
        ld1125_data.occ_dis = data_vals_str.toFloat();
      }

      if (test_mode) {

        String str_vals = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());

        String str_vals_txt = str_vals.substring(0, str_vals.indexOf('='));

        if (str_vals_txt == "str") {
          String str_vals_str = str_vals.substring(str_vals.indexOf('=') + 1, str_vals.length());
          ld1125_data.occ_str = str_vals_str.toFloat();
        }
      }
    }
  }

#endif

  if (not is_soft) {

    String data_str = HS->readStringUntil('\n');

    String data_type = data_str.substring(0, data_str.indexOf(' '));

    if (data_type == ld1125_mov_txt) {

      ld1125_data.dis_type = "mov";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String data_vals_txt = data_vals.substring(0, data_vals.indexOf('='));

      if (data_vals_txt == "dis") {
        String data_vals_str = data_vals.substring(data_vals.indexOf('=') + 1, data_vals.length());
        ld1125_data.mov_dis = data_vals_str.toFloat();
      }

      if (test_mode) {

        String str_vals = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());

        String str_vals_txt = str_vals.substring(0, str_vals.indexOf('='));

        if (str_vals_txt == "str") {
          String str_vals_str = str_vals.substring(str_vals.indexOf('=') + 1, str_vals.length());
          ld1125_data.mov_str = str_vals_str.toFloat();
        }
      }
    }

    else if (data_type == ld1125_occ_txt) {

      ld1125_data.dis_type = "occ";

      String data_vals = data_str.substring(data_str.indexOf(' ') + 1, data_str.length());

      String data_vals_txt = data_vals.substring(0, data_vals.indexOf('='));

      if (data_vals_txt == "dis") {
        String data_vals_str = data_vals.substring(data_vals.indexOf('=') + 1, data_vals.length());
        ld1125_data.occ_dis = data_vals_str.toFloat();
      }

      if (test_mode) {

        String str_vals = data_vals.substring(data_vals.indexOf(' ') + 1, data_vals.length());

        String str_vals_txt = str_vals.substring(0, str_vals.indexOf('='));

        if (str_vals_txt == "str") {
          String str_vals_str = str_vals.substring(str_vals.indexOf('=') + 1, str_vals.length());
          ld1125_data.occ_str = str_vals_str.toFloat();
        }
      }
    }
  }
}

String HLK_LD1125::getDisType() {
  return ld1125_data.dis_type;
}

float HLK_LD1125::getOccDis() {
  return ld1125_data.occ_dis;
}

float HLK_LD1125::getMovDis() {
  return ld1125_data.mov_dis;
}

float HLK_LD1125::getOccStr() {
  return ld1125_data.occ_str;
}

float HLK_LD1125::getMovStr() {
  return ld1125_data.mov_str;
}

void HLK_LD1125::getAllSettings() {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String get_all_suc = "";

    SS->println(ld1125_get_all_str);

    get_all_suc = SS->readStringUntil('\n');

    if (get_all_suc == ld1125_get_all_suc_str) {

      for (int i = 0; i < ld1125_conf_vals_len; i++) {

        String conf_data_str = SS->readStringUntil('\n');

        String conf_data_type = conf_data_str.substring(0, conf_data_str.indexOf(' '));

        String conf_data_type_split = conf_data_str.substring(conf_data_str.indexOf(' ') + 1, conf_data_str.length());

        String conf_data_type_split_suc = conf_data_type_split.substring(0, conf_data_type_split.indexOf(' '));

        if (conf_data_type_split_suc == "is") {

          String conf_data_type_split_val = conf_data_type_split.substring(conf_data_type_split.indexOf(' '), conf_data_type_split.length());

          if (conf_data_type == "rmax")
            ld1125_conf_data.rmax = conf_data_type_split_val.toFloat();

          else if (conf_data_type == "mth1_mov")
            ld1125_conf_data.mth1_mov = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth2_mov")
            ld1125_conf_data.mth2_mov = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth3_mov")
            ld1125_conf_data.mth3_mov = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth1_occ")
            ld1125_conf_data.mth1_occ = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth2_occ")
            ld1125_conf_data.mth2_occ = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth3_occ")
            ld1125_conf_data.mth3_occ = conf_data_type_split_val.toInt();

          else if (conf_data_type == "ts_on")
            ld1125_conf_data.ts_on = conf_data_type_split_val.toInt();

          else if (conf_data_type == "ts_off")
            ld1125_conf_data.ts_off = conf_data_type_split_val.toInt();

          else if (conf_data_type == "output_mode")
            ld1125_conf_data.output_mode = conf_data_type_split_val.toInt();
        }
      }
    }
  }

#endif

  if (not is_soft) {

    String get_all_suc = "";

    HS->println(ld1125_get_all_str);

    //HS->readStringUntil('\n');

    get_all_suc = HS->readStringUntil('\n');

    if (get_all_suc == ld1125_get_all_suc_str) {

      for (int i = 0; i < ld1125_conf_vals_len; i++) {

        String conf_data_str = HS->readStringUntil('\n');

        String conf_data_type = conf_data_str.substring(0, conf_data_str.indexOf(' '));

        String conf_data_type_split = conf_data_str.substring(conf_data_str.indexOf(' ') + 1, conf_data_str.length());

        String conf_data_type_split_suc = conf_data_type_split.substring(0, conf_data_type_split.indexOf(' '));

        if (conf_data_type_split_suc == "is") {

          String conf_data_type_split_val = conf_data_type_split.substring(conf_data_type_split.indexOf(' '), conf_data_type_split.length());

          if (conf_data_type == "rmax")
            ld1125_conf_data.rmax = conf_data_type_split_val.toFloat();

          else if (conf_data_type == "mth1_mov")
            ld1125_conf_data.mth1_mov = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth2_mov")
            ld1125_conf_data.mth2_mov = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth3_mov")
            ld1125_conf_data.mth3_mov = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth1_occ")
            ld1125_conf_data.mth1_occ = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth2_occ")
            ld1125_conf_data.mth2_occ = conf_data_type_split_val.toInt();

          else if (conf_data_type == "mth3_occ")
            ld1125_conf_data.mth3_occ = conf_data_type_split_val.toInt();

          else if (conf_data_type == "ts_on")
            ld1125_conf_data.ts_on = conf_data_type_split_val.toInt();

          else if (conf_data_type == "ts_off")
            ld1125_conf_data.ts_off = conf_data_type_split_val.toInt();

          else if (conf_data_type == "output_mode")
            ld1125_conf_data.output_mode = conf_data_type_split_val.toInt();
        }
      }
    }
  }
}

float HLK_LD1125::getRmax() {
  return ld1125_conf_data.rmax;
}

uint16_t HLK_LD1125::getMth1Mov() {
  return ld1125_conf_data.mth1_mov;
}

uint16_t HLK_LD1125::getMth2Mov() {
  return ld1125_conf_data.mth2_mov;
}

uint16_t HLK_LD1125::getMth3Mov() {
  return ld1125_conf_data.mth3_mov;
}

uint16_t HLK_LD1125::getMth1Occ() {
  return ld1125_conf_data.mth1_occ;
}

uint16_t HLK_LD1125::getMth2Occ() {
  return ld1125_conf_data.mth2_occ;
}

uint16_t HLK_LD1125::getMth3Occ() {
  return ld1125_conf_data.mth3_occ;
}

uint16_t HLK_LD1125::getTsOn() {
  return ld1125_conf_data.ts_on;
}

uint16_t HLK_LD1125::getTsOff() {
  return ld1125_conf_data.ts_off;
}

bool HLK_LD1125::getOutputMode() {
  return ld1125_conf_data.output_mode;
}

bool HLK_LD1125::saveAllSettings() {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    SS->println(ld1125_save_str);

    SS->readStringUntil('\n');

    String save_suc = SS->readStringUntil('\n');
    String save_suc2 = SS->readStringUntil('\n');

    return save_suc == ld1125_save_suc_str and save_suc2 == ld1125_save_suc2_str;
  }

#endif

  if (not is_soft) {

    HS->println(ld1125_save_str);

    HS->readStringUntil('\n');

    String save_suc = HS->readStringUntil('\n');
    String save_suc2 = HS->readStringUntil('\n');

    return save_suc == ld1125_save_suc_str and save_suc2 == ld1125_save_suc2_str;
  }
}

bool HLK_LD1125::setRmax(float rmax) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_rmax_suc_str = "received message: rmax=" + String(rmax) + "\r";
    String set_rmax_suc2_str = "rmax is " + String(rmax) + "\r";

    SS->println("rmax=" + String(rmax));

    SS->readStringUntil('\n');

    String set_rmax_suc = SS->readStringUntil('\n');
    String set_rmax_suc2 = SS->readStringUntil('\n');

    return set_rmax_suc == set_rmax_suc_str and set_rmax_suc2 == set_rmax_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_rmax_suc_str = "received message: rmax=" + String(rmax) + "\r";
    String set_rmax_suc2_str = "rmax is " + String(rmax) + "\r";

    HS->println("rmax=" + String(rmax));

    HS->readStringUntil('\n');

    String set_rmax_suc = HS->readStringUntil('\n');
    String set_rmax_suc2 = HS->readStringUntil('\n');

    return set_rmax_suc == set_rmax_suc_str and set_rmax_suc2 == set_rmax_suc2_str;
  }
}

bool HLK_LD1125::setMth1Mov(uint16_t mth1_mov) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_mth1_mov_suc_str = "received message: mth1_mov=" + String(mth1_mov) + "\r";
    String set_mth1_mov_suc2_str = "mth1_mov is " + String(mth1_mov) + "\r";

    SS->println("mth1_mov=" + String(mth1_mov));

    SS->readStringUntil('\n');

    String set_mth1_mov_suc = SS->readStringUntil('\n');
    String set_mth1_mov_suc2 = SS->readStringUntil('\n');

    return set_mth1_mov_suc == set_mth1_mov_suc_str and set_mth1_mov_suc2 == set_mth1_mov_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_mth1_mov_suc_str = "received message: mth1_mov=" + String(mth1_mov) + "\r";
    String set_mth1_mov_suc2_str = "mth1_mov is " + String(mth1_mov) + "\r";

    HS->println("mth1_mov=" + String(mth1_mov));

    HS->readStringUntil('\n');

    String set_mth1_mov_suc = HS->readStringUntil('\n');
    String set_mth1_mov_suc2 = HS->readStringUntil('\n');

    return set_mth1_mov_suc == set_mth1_mov_suc_str and set_mth1_mov_suc2 == set_mth1_mov_suc2_str;
  }
}

bool HLK_LD1125::setMth2Mov(uint16_t mth2_mov) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_mth2_mov_suc_str = "received message: mth2_mov=" + String(mth2_mov) + "\r";
    String set_mth2_mov_suc2_str = "mth2_mov is " + String(mth2_mov) + "\r";

    SS->println("mth2_mov=" + String(mth2_mov));

    SS->readStringUntil('\n');

    String set_mth2_mov_suc = SS->readStringUntil('\n');
    String set_mth2_mov_suc2 = SS->readStringUntil('\n');

    return set_mth2_mov_suc == set_mth2_mov_suc_str and set_mth2_mov_suc2 == set_mth2_mov_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_mth2_mov_suc_str = "received message: mth2_mov=" + String(mth2_mov) + "\r";
    String set_mth2_mov_suc2_str = "mth2_mov is " + String(mth2_mov) + "\r";

    HS->println("mth2_mov=" + String(mth2_mov));

    HS->readStringUntil('\n');

    String set_mth2_mov_suc = HS->readStringUntil('\n');
    String set_mth2_mov_suc2 = HS->readStringUntil('\n');

    return set_mth2_mov_suc == set_mth2_mov_suc_str and set_mth2_mov_suc2 == set_mth2_mov_suc2_str;
  }
}

bool HLK_LD1125::setMth3Mov(uint16_t mth3_mov) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_mth3_mov_suc_str = "received message: mth2_mov=" + String(mth3_mov) + "\r";
    String set_mth3_mov_suc2_str = "mth3_mov is " + String(mth3_mov) + "\r";

    SS->println("mth3_mov=" + String(mth3_mov));

    SS->readStringUntil('\n');

    String set_mth3_mov_suc = SS->readStringUntil('\n');
    String set_mth3_mov_suc2 = SS->readStringUntil('\n');

    return set_mth3_mov_suc == set_mth3_mov_suc_str and set_mth3_mov_suc2 == set_mth3_mov_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_mth3_mov_suc_str = "received message: mth2_mov=" + String(mth3_mov) + "\r";
    String set_mth3_mov_suc2_str = "mth3_mov is " + String(mth3_mov) + "\r";

    HS->println("mth3_mov=" + String(mth3_mov));

    HS->readStringUntil('\n');

    String set_mth3_mov_suc = HS->readStringUntil('\n');
    String set_mth3_mov_suc2 = HS->readStringUntil('\n');

    return set_mth3_mov_suc == set_mth3_mov_suc_str and set_mth3_mov_suc2 == set_mth3_mov_suc2_str;
  }
}

bool HLK_LD1125::setMth1Occ(uint16_t mth1_occ) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_mth1_occ_suc_str = "received message: mth1_occ=" + String(mth1_occ) + "\r";
    String set_mth1_occ_suc2_str = "mth1_occ is " + String(mth1_occ) + "\r";

    SS->println("mth1_occ=" + String(mth1_occ));

    SS->readStringUntil('\n');

    String set_mth1_occ_suc = SS->readStringUntil('\n');
    String set_mth1_occ_suc2 = SS->readStringUntil('\n');

    return set_mth1_occ_suc == set_mth1_occ_suc_str and set_mth1_occ_suc2 == set_mth1_occ_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_mth1_occ_suc_str = "received message: mth1_occ=" + String(mth1_occ) + "\r";
    String set_mth1_occ_suc2_str = "mth1_occ is " + String(mth1_occ) + "\r";

    HS->println("mth1_occ=" + String(mth1_occ));

    HS->readStringUntil('\n');

    String set_mth1_occ_suc = HS->readStringUntil('\n');
    String set_mth1_occ_suc2 = HS->readStringUntil('\n');

    return set_mth1_occ_suc == set_mth1_occ_suc_str and set_mth1_occ_suc2 == set_mth1_occ_suc2_str;
  }
}

bool HLK_LD1125::setMth2Occ(uint16_t mth2_occ) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_mth2_occ_suc_str = "received message: mth2_occ=" + String(mth2_occ) + "\r";
    String set_mth2_occ_suc2_str = "mth2_occ is " + String(mth2_occ) + "\r";

    SS->println("mth2_occ=" + String(mth2_occ));

    SS->readStringUntil('\n');

    String set_mth2_occ_suc = SS->readStringUntil('\n');
    String set_mth2_occ_suc2 = SS->readStringUntil('\n');

    return set_mth2_occ_suc == set_mth2_occ_suc_str and set_mth2_occ_suc2 == set_mth2_occ_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_mth2_occ_suc_str = "received message: mth2_occ=" + String(mth2_occ) + "\r";
    String set_mth2_occ_suc2_str = "mth2_occ is " + String(mth2_occ) + "\r";

    HS->println("mth2_occ=" + String(mth2_occ));

    HS->readStringUntil('\n');

    String set_mth2_occ_suc = HS->readStringUntil('\n');
    String set_mth2_occ_suc2 = HS->readStringUntil('\n');

    return set_mth2_occ_suc == set_mth2_occ_suc_str and set_mth2_occ_suc2 == set_mth2_occ_suc2_str;
  }
}

bool HLK_LD1125::setMth3Occ(uint16_t mth3_occ) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_mth3_occ_suc_str = "received message: mth3_occ=" + String(mth3_occ) + "\r";
    String set_mth3_occ_suc2_str = "mth3_occ is " + String(mth3_occ) + "\r";

    SS->println("mth3_occ=" + String(mth3_occ));

    SS->readStringUntil('\n');

    String set_mth3_occ_suc = SS->readStringUntil('\n');
    String set_mth3_occ_suc2 = SS->readStringUntil('\n');

    return set_mth3_occ_suc == set_mth3_occ_suc_str and set_mth3_occ_suc2 == set_mth3_occ_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_mth3_occ_suc_str = "received message: mth3_occ=" + String(mth3_occ) + "\r";
    String set_mth3_occ_suc2_str = "mth3_occ is " + String(mth3_occ) + "\r";

    HS->println("mth3_occ=" + String(mth3_occ));

    HS->readStringUntil('\n');

    String set_mth3_occ_suc = HS->readStringUntil('\n');
    String set_mth3_occ_suc2 = HS->readStringUntil('\n');

    return set_mth3_occ_suc == set_mth3_occ_suc_str and set_mth3_occ_suc2 == set_mth3_occ_suc2_str;
  }
}

bool HLK_LD1125::setTsOn(uint16_t ts_on) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_ts_on_suc_str = "received message: ts_on=" + String(ts_on) + "\r";
    String set_ts_on_suc2_str = "ts_on is " + String(ts_on) + "\r";

    SS->println("ts_on=" + String(ts_on));

    SS->readStringUntil('\n');

    String set_ts_on_suc = SS->readStringUntil('\n');
    String set_ts_on_suc2 = SS->readStringUntil('\n');

    return set_ts_on_suc == set_ts_on_suc_str and set_ts_on_suc2 == set_ts_on_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_ts_on_suc_str = "received message: ts_on=" + String(ts_on) + "\r";
    String set_ts_on_suc2_str = "ts_on is " + String(ts_on) + "\r";

    HS->println("ts_on=" + String(ts_on));

    HS->readStringUntil('\n');

    String set_ts_on_suc = HS->readStringUntil('\n');
    String set_ts_on_suc2 = HS->readStringUntil('\n');

    return set_ts_on_suc == set_ts_on_suc_str and set_ts_on_suc2 == set_ts_on_suc2_str;
  }
}

bool HLK_LD1125::setTsOff(uint16_t ts_off) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_ts_off_suc_str = "received message: ts_off=" + String(ts_off) + "\r";
    String set_ts_off_suc2_str = "ts_off is " + String(ts_off) + "\r";

    SS->println("ts_off=" + String(ts_off));

    SS->readStringUntil('\n');

    String set_ts_off_suc = SS->readStringUntil('\n');
    String set_ts_off_suc2 = SS->readStringUntil('\n');

    return set_ts_off_suc == set_ts_off_suc_str and set_ts_off_suc2 == set_ts_off_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_ts_off_suc_str = "received message: ts_off=" + String(ts_off) + "\r";
    String set_ts_off_suc2_str = "ts_off is " + String(ts_off) + "\r";

    HS->println("ts_off=" + String(ts_off));

    HS->readStringUntil('\n');

    String set_ts_off_suc = HS->readStringUntil('\n');
    String set_ts_off_suc2 = HS->readStringUntil('\n');

    return set_ts_off_suc == set_ts_off_suc_str and set_ts_off_suc2 == set_ts_off_suc2_str;
  }
}

bool HLK_LD1125::setOutputMode(bool output_mode) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    String set_output_mode_suc_str = "received message: output_mode=" + String(output_mode) + "\r";
    String set_output_mode_suc2_str = "output_mode is " + String(output_mode) + "\r";

    SS->println("output_mode=" + String(output_mode));

    SS->readStringUntil('\n');

    String set_output_mode_suc = SS->readStringUntil('\n');
    String set_output_mode_suc2 = SS->readStringUntil('\n');

    return set_output_mode_suc == set_output_mode_suc_str and set_output_mode_suc2 == set_output_mode_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_output_mode_suc_str = "received message: output_mode=" + String(output_mode) + "\r";
    String set_output_mode_suc2_str = "output_mode is " + String(output_mode) + "\r";

    HS->println("output_mode=" + String(output_mode));

    HS->readStringUntil('\n');

    String set_output_mode_suc = HS->readStringUntil('\n');
    String set_output_mode_suc2 = HS->readStringUntil('\n');

    return set_output_mode_suc == set_output_mode_suc_str and set_output_mode_suc2 == set_output_mode_suc2_str;
  }
}

bool HLK_LD1125::setTestMode(bool test_mode) {

#ifndef _BOARD_GENERIC_STM32F103C_H_

  if (is_soft) {

    this->test_mode = test_mode;

    String set_test_mode_suc_str = "received message: test_mode=" + String(test_mode) + "\r";
    String set_test_mode_suc2_str = "test_mode is " + String(test_mode) + "\r";

    SS->println("testt_mode=" + String(test_mode));

    SS->readStringUntil('\n');

    String set_test_mode_suc = SS->readStringUntil('\n');
    String set_test_mode_suc2 = SS->readStringUntil('\n');

    if (set_test_mode_suc == set_test_mode_suc_str and set_test_mode_suc2 == set_test_mode_suc2_str)
      this->test_mode = test_mode;

    return set_test_mode_suc == set_test_mode_suc_str and set_test_mode_suc2 == set_test_mode_suc2_str;
  }

#endif

  if (not is_soft) {

    String set_test_mode_suc_str = "received message: test_mode=" + String(test_mode) + "\r";
    String set_test_mode_suc2_str = "test_mode is " + String(test_mode) + "\r";

    HS->println("test_mode=" + String(test_mode));

    HS->readStringUntil('\n');

    String set_test_mode_suc = HS->readStringUntil('\n');
    String set_test_mode_suc2 = HS->readStringUntil('\n');

    Serial.println(set_test_mode_suc);
    Serial.println(set_test_mode_suc2);

    if (set_test_mode_suc == set_test_mode_suc_str and set_test_mode_suc2 == set_test_mode_suc2_str)
      this->test_mode = test_mode;

    return set_test_mode_suc == set_test_mode_suc_str and set_test_mode_suc2 == set_test_mode_suc2_str;
  }
}
