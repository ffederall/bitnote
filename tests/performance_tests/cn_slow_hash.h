// Copyright (c) 2018, The Bitnote Developers.
// Portions Copyright (c) 2012-2013, The CryptoNote Developers.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include "crypto/crypto.h"
#include "cryptonote_core/cryptonote_basic.h"

class test_cn_slow_hash
{
public:
  static const size_t loop_count = 10;

#pragma pack(push, 1)
  struct data_t
  {
    char data[13];
  };
#pragma pack(pop)

  static_assert(13 == sizeof(data_t), "Invalid structure size");

  bool init()
  {
    if (!epee::string_tools::hex_to_pod("63617665617420656d70746f72", m_data))
      return false;

    if (!epee::string_tools::hex_to_pod("bbec2cacf69866a8e740380fe7b818fc78f8571221742d729d9d02d7f8989b87", m_expected_hash))
      return false;

    if (!epee::string_tools::hex_to_pod("98c48cda9ab5d26ef2717e7375f665fc18b703aac6c059bb814685f21946647f", m_expected_hash_dark))
      return false;


    return true;
  }

  bool test()
  {
    crypto::hash hash;
    crypto::hash hash_dark;

    crypto::cn_slow_hash(&m_data, sizeof(m_data), hash, 0);
    crypto::cn_slow_hash(&m_data, sizeof(m_data), hash_dark, 1);
    return (hash == m_expected_hash) && (hash_dark == m_expected_hash_dark);
  }

private:
  data_t m_data;
  crypto::hash m_expected_hash;
  crypto::hash m_expected_hash_dark;
};
