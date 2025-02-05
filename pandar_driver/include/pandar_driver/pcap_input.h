/******************************************************************************
 * Copyright 2019 The Hesai Technology Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#pragma once

#include <pcap.h>
#include <string>
#include "pandar_driver/input.h"

namespace pandar_driver
{
class PcapInput : public Input
{
public:
  PcapInput(uint16_t port, uint16_t gps_port, std::string path, std::string model);
  ~PcapInput();

  PacketType getPacket(pandar_msgs::PandarPacket* pandar_pkt) override;

private:
  void initTimeIndexMap();
  std::string pcap_path_;
  std::string frame_id_;
  int ts_index_;
  int utc_index_;
  std::map<std::string, std::pair<int, int>> time_index_map_;

  pcap_t* pcap_;
  char errbuf_[PCAP_ERRBUF_SIZE];
  bpf_program pcap_filter_;

  size_t packet_count_;
  int64_t last_pkt_ts_;
  int64_t last_time_;
};

}  // namespace pandar_driver
