// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include "MessageBuffer.hpp"

#include "silkit/services/lin/LinDatatypes.hpp"

namespace SilKit {
namespace Services {
namespace Lin {
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinFrame& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinSendFrameRequest& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinSendFrameHeaderRequest& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinTransmission& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinWakeupPulse& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinControllerConfig& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinControllerStatusUpdate& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinFrameResponse& msg);
void Serialize(SilKit::Core::MessageBuffer& buffer, const LinFrameResponseUpdate& msg);

void Deserialize(SilKit::Core::MessageBuffer& buffer, LinFrame& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinSendFrameRequest& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinSendFrameHeaderRequest& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinTransmission& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinWakeupPulse& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinControllerConfig& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinControllerStatusUpdate& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinFrameResponse& out);
void Deserialize(SilKit::Core::MessageBuffer& buffer, LinFrameResponseUpdate& out);
} // namespace Lin    
} // namespace Services
} // namespace SilKit