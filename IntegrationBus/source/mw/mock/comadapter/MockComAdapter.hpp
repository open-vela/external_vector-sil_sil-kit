// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include "ib/mw/IComAdapter.hpp"
#include "ib/mw/sync/SyncDatatypes.hpp"
#include "ib/mw/logging/LoggingDatatypes.hpp"
#include "ib/mw/logging/spdlog.hpp"

#include "ib/sim/fwd_decl.hpp"
#include "ib/sim/can/CanDatatypes.hpp"
#include "ib/sim/eth/EthDatatypes.hpp"
#include "ib/sim/fr/FrDatatypes.hpp"
#include "ib/sim/lin/LinDatatypes.hpp"
#include "ib/sim/io/IoDatatypes.hpp"
#include "ib/sim/generic/GenericMessageDatatypes.hpp"

#include "spdlog/sinks/null_sink.h"

#ifdef SendMessage
#undef SendMessage
#endif

namespace ib {
namespace mw {
namespace test {

class DummyComAdapter : public IComAdapter
{
public:
    DummyComAdapter()
    {
        logger = spdlog::default_logger();
    }

    auto CreateCanController(const std::string& /*canonicalName*/) -> sim::can::ICanController* { return nullptr; }
    auto CreateEthController(const std::string& /*canonicalName*/) -> sim::eth::IEthController* { return nullptr; }
    auto CreateFlexrayController(const std::string& /*canonicalName*/) -> sim::fr::IFrController* { return nullptr; }
    auto CreateLinController(const std::string& /*canonicalName*/) -> sim::lin::ILinController* { return nullptr; }
    auto CreateAnalogIn(const std::string& /*canonicalName*/) -> sim::io::IAnalogInPort* { return nullptr; }
    auto CreateDigitalIn(const std::string& /*canonicalName*/) -> sim::io::IDigitalInPort* { return nullptr; }
    auto CreatePwmIn(const std::string& /*canonicalName*/) -> sim::io::IPwmInPort* { return nullptr; }
    auto CreatePatternIn(const std::string& /*canonicalName*/) -> sim::io::IPatternInPort* { return nullptr; }
    auto CreateAnalogOut(const std::string& /*canonicalName*/) -> sim::io::IAnalogOutPort* { return nullptr; }
    auto CreateDigitalOut(const std::string& /*canonicalName*/) -> sim::io::IDigitalOutPort* { return nullptr; }
    auto CreatePwmOut(const std::string& /*canonicalName*/) -> sim::io::IPwmOutPort* { return nullptr; }
    auto CreatePatternOut(const std::string& /*canonicalName*/) -> sim::io::IPatternOutPort* { return nullptr; }
    auto CreateGenericPublisher(const std::string& /*canonicalName*/) -> sim::generic::IGenericPublisher* { return nullptr; }
    auto CreateGenericSubscriber(const std::string& /*canonicalName*/) -> sim::generic::IGenericSubscriber* { return nullptr; }

    auto GetSyncMaster() -> sync::ISyncMaster* { return nullptr; }
    auto GetParticipantController() -> sync::IParticipantController* { return nullptr; }
    auto GetSystemMonitor() -> sync::ISystemMonitor* { return nullptr; }
    auto GetSystemController() -> sync::ISystemController* { return nullptr; }
    auto GetLogger() -> std::shared_ptr<spdlog::logger>& { return logger; }

    void RegisterCanSimulator(sim::can::IIbToCanSimulator* /*canonicalName*/) {}
    void RegisterEthSimulator(sim::eth::IIbToEthSimulator* /*canonicalName*/) {}
    void RegisterFlexraySimulator(sim::fr::IIbToFrBusSimulator* /*canonicalName*/) {}
    void RegisterLinSimulator(sim::lin::IIbToLinSimulator* /*canonicalName*/) {}

    void SendIbMessage(EndpointAddress /*from*/, sim::can::CanMessage&& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::can::CanMessage& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::can::CanTransmitAcknowledge& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::can::CanControllerStatus& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::can::CanConfigureBaudrate& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::can::CanSetControllerMode& /*msg*/) {}

    void SendIbMessage(EndpointAddress /*from*/, sim::eth::EthMessage&& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::eth::EthMessage& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::eth::EthTransmitAcknowledge& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::eth::EthStatus& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::eth::EthSetMode& /*msg*/) {}

    void SendIbMessage(EndpointAddress /*from*/, sim::fr::FrMessage&& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::FrMessage& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, sim::fr::FrMessageAck&& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::FrMessageAck& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::FrSymbol& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::FrSymbolAck& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::CycleStart& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::HostCommand& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::ControllerConfig& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::TxBufferConfigUpdate& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::TxBufferUpdate& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::fr::ControllerStatus& /*msg*/) {}

    void SendIbMessage(EndpointAddress /*from*/, const sim::lin::LinMessage& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::lin::RxRequest& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::lin::TxAcknowledge& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::lin::WakeupRequest& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::lin::ControllerConfig& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::lin::SlaveConfiguration& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::lin::SlaveResponse& /*msg*/) {}

    void SendIbMessage(EndpointAddress /*from*/, const sim::io::AnalogIoMessage& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::io::DigitalIoMessage& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, sim::io::PatternIoMessage&& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::io::PatternIoMessage& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::io::PwmIoMessage& /*msg*/) {}

    void SendIbMessage(EndpointAddress /*from*/, sim::generic::GenericMessage&& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sim::generic::GenericMessage& /*msg*/) {}
    void SendIbMessage_proxy(EndpointAddress /*from*/, const sim::generic::GenericMessage& /*msg*/) {}

    void SendIbMessage(EndpointAddress /*from*/, const sync::NextSimTask& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sync::Tick& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sync::TickDone& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sync::QuantumRequest& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sync::QuantumGrant& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sync::ParticipantStatus& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sync::ParticipantCommand& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const sync::SystemCommand& /*msg*/) {}

    void SendIbMessage(EndpointAddress /*from*/, logging::LogMsg&& /*msg*/) {}
    void SendIbMessage(EndpointAddress /*from*/, const logging::LogMsg& /*msg*/) {}

    void OnAllMessagesDelivered(std::function<void(void)> /*callback*/) {}
    void FlushSendBuffers() {}
    void RegisterNewPeerCallback(std::function<void(void)> /*callback*/) {}

    std::shared_ptr<spdlog::logger> logger;
};

// ================================================================================
//  Inline Implementations
// ================================================================================

} // namespace test
} // namespace mw
} // namespace ib
