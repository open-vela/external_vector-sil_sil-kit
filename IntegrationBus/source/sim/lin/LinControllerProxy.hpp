// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include <memory>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "ib/sim/lin/ILinController.hpp"
#include "ib/mw/fwd_decl.hpp"

#include "IIbToLinControllerProxy.hpp"
#include "IParticipantInternal.hpp"
#include "ITraceMessageSource.hpp"

namespace ib {
namespace sim {
namespace lin {

class LinControllerProxy
    : public ILinController
    , public IIbToLinControllerProxy
    , public extensions::ITraceMessageSource
    , public mw::IIbServiceEndpoint
{
public:
    // ----------------------------------------
    // Public Data Types

public:
    // ----------------------------------------
    // Constructors and Destructor
    LinControllerProxy() = delete;
    LinControllerProxy(const LinControllerProxy&) = default;
    LinControllerProxy(LinControllerProxy&&) = default;
    LinControllerProxy(mw::IParticipantInternal* participant, ILinController* facade = nullptr);

public:
    // ----------------------------------------
    // Operator Implementations
    LinControllerProxy& operator=(LinControllerProxy& other) = default;
    LinControllerProxy& operator=(LinControllerProxy&& other) = default;

public:
    // ----------------------------------------
    // Public interface methods
    //
    // ILinController
    void Init(ControllerConfig config) override;
    auto Status() const noexcept->ControllerStatus override;

    void SendFrame(Frame frame, FrameResponseType responseType) override;
    void SendFrame(Frame frame, FrameResponseType responseType, std::chrono::nanoseconds timestamp) override;
    void SendFrameHeader(LinIdT linId) override;
    void SendFrameHeader(LinIdT linId, std::chrono::nanoseconds timestamp) override;
    void SetFrameResponse(Frame frame, FrameResponseMode mode) override;
    void SetFrameResponses(std::vector<FrameResponse> responses) override;

    void GoToSleep() override;
    void GoToSleepInternal() override;
    void Wakeup() override;
    void WakeupInternal() override;

    void RegisterFrameStatusHandler(FrameStatusHandler handler) override;
    void RegisterGoToSleepHandler(GoToSleepHandler handler) override;
    void RegisterWakeupHandler(WakeupHandler handler) override;
    void RegisterFrameResponseUpdateHandler(FrameResponseUpdateHandler handler) override;

    // IIbToLinController
    void ReceiveIbMessage(const IIbServiceEndpoint* from, const Transmission& msg) override;
    void ReceiveIbMessage(const IIbServiceEndpoint* from, const WakeupPulse& msg) override;
    void ReceiveIbMessage(const IIbServiceEndpoint* from, const ControllerConfig& msg) override;
    void ReceiveIbMessage(const IIbServiceEndpoint* from, const FrameResponseUpdate& msg) override;

public:
    // ----------------------------------------
    // Public interface methods

    //ITraceMessageSource
    inline void AddSink(extensions::ITraceMessageSink* sink) override;

    // IIbServiceEndpoint
    inline void SetServiceDescriptor(const mw::ServiceDescriptor& serviceDescriptor) override;
    inline auto GetServiceDescriptor() const -> const mw::ServiceDescriptor & override;

private:
//    // ----------------------------------------
//    // private data types

private:
    // ----------------------------------------
    // private methods
    void SetControllerStatus(ControllerStatus status);

    template <typename MsgT>
    inline void SendIbMessage(MsgT&& msg);

private:
    // ----------------------------------------
    // private members
    mw::IParticipantInternal* _participant;
    mw::logging::ILogger* _logger;
    ::ib::mw::ServiceDescriptor _serviceDescriptor;
    ILinController* _facade{ nullptr };

    ControllerMode   _controllerMode{ControllerMode::Inactive};
    ControllerStatus _controllerStatus{ControllerStatus::Unknown};

    std::vector<FrameStatusHandler>         _frameStatusHandler;
    std::vector<GoToSleepHandler>           _goToSleepHandler;
    std::vector<WakeupHandler>              _wakeupHandler;
    std::vector<FrameResponseUpdateHandler> _frameResponseUpdateHandler;

    extensions::Tracer _tracer;
};

//// ==================================================================
//  Inline Implementations
// ==================================================================
void LinControllerProxy::AddSink(extensions::ITraceMessageSink* sink)
{
    _tracer.AddSink(mw::EndpointAddress{}, *sink);
}

void LinControllerProxy::SetServiceDescriptor(const mw::ServiceDescriptor& serviceDescriptor)
{
    _serviceDescriptor = serviceDescriptor;
}
auto LinControllerProxy::GetServiceDescriptor() const -> const mw::ServiceDescriptor&
{
    return _serviceDescriptor;
}
} // namespace lin
} // namespace sim
} // namespace ib
