#include <utility>
#include "VaultClient.h"

WrappedSecretAppRoleStrategy::WrappedSecretAppRoleStrategy(std::string role_id, const Token& token)
  : role_id_(std::move(role_id))
  , token_(token)
  {}

optional<AuthenticationResponse> WrappedSecretAppRoleStrategy::authenticate(const VaultClient &vaultClient) {
  auto secret_id = Unwrap::unwrap(vaultClient, token_);

  return secret_id
    ? AppRoleStrategy(role_id_, secret_id.value()).authenticate(vaultClient)
    : std::experimental::nullopt;
}