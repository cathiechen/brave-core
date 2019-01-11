/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_BAT_CLIENT_H_
#define BRAVELEDGER_BAT_CLIENT_H_

#include <string>
#include <vector>
#include <mutex>

#include "bat/ledger/ledger_callback_handler.h"
#include "bat/ledger/publisher_info.h"
#include "bat_helper.h"

namespace bat_ledger {
class LedgerImpl;
}

namespace braveledger_bat_client {

class BatClient {
 public:
  explicit BatClient(bat_ledger::LedgerImpl* ledger);
  ~BatClient();

  void registerPersona();
  void requestCredentialsCallback(bool result, const std::string& response,
      const std::map<std::string, std::string>& headers);
  void registerPersonaCallback(bool result, const std::string& response,
      const std::map<std::string, std::string>& headers);
  std::string getWalletPassphrase() const;
  void walletPropertiesCallback(bool success, const std::string& response,
      const std::map<std::string, std::string>& headers);
  void recoverWallet(const std::string& pass_phrase);
  void getGrant(const std::string& lang, const std::string& for_payment_id,
      const std::string& safetynet_token);
  void setGrant(const std::string& captcha_response,
      const std::string& promotion_id, const std::string& safetynet_token);
  void getGrantCaptcha();
  void getGrantViaSafetynetCheck();
  void getWalletProperties();

  void continueRecover(int result, size_t *written,
      std::vector<uint8_t>& new_seed);

  void OnNicewareListLoaded(const std::string& pass_phrase,
      ledger::Result result,
      const std::string& data);

 private:
  void getGrantCaptchaCallback(bool result, const std::string& response,
      const std::map<std::string, std::string>& headers);
  void getGrantCallback(bool result, const std::string& response,
      const std::map<std::string, std::string>& headers);
  void setGrantCallback(bool result, const std::string& response,
      const std::map<std::string, std::string>& headers,
      bool is_satetynet_check);
  void recoverWalletPublicKeyCallback(bool result, const std::string& response,
      const std::map<std::string, std::string>& headers);
  void recoverWalletCallback(bool result, const std::string& response,
      const std::map<std::string, std::string>& headers,
      const std::string& payment_id);
  void getGrantViaSafetynetCheckCallback(bool result,
      const std::string& response,
      const std::map<std::string, std::string>& headers);
  std::string getAnonizeProof(const std::string& registrar_vk,
      const std::string& id, std::string& pre_flight);

  bat_ledger::LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace braveledger_bat_client

#endif  // BRAVELEDGER_BAT_CLIENT_H_
