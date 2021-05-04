// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include "IReplayDataController.hpp"
#include "ib/sim/generic/IGenericPublisher.hpp"
#include "ib/sim/generic/IIbToGenericPublisher.hpp"
#include "GenericPublisher.hpp"

namespace ib {
namespace sim {
namespace generic {

class GenericPublisherReplay
    : public IGenericPublisher
    , public IIbToGenericPublisher
    , public mw::sync::ITimeConsumer
    , public extensions::ITraceMessageSource
    , public tracing::IReplayDataController
{
public:
    // Constructors 
    GenericPublisherReplay() = delete;
    GenericPublisherReplay(mw::IComAdapter* comAdapter, cfg::GenericPort config, mw::sync::ITimeProvider* timeProvider);

public:
    // ----------------------------------------
    // Public interface methods
    //
    // IGenericPublisher
    void Publish(std::vector<uint8_t> data) override;
    void Publish(const uint8_t* data, std::size_t size) override;

    auto Config() const -> const cfg::GenericPort& override;

    void SetEndpointAddress(const mw::EndpointAddress& endpointAddress) override;
    auto EndpointAddress() const -> const mw::EndpointAddress& override;

    // ib::mw::sync::ITimeConsumer
    void SetTimeProvider(ib::mw::sync::ITimeProvider* timeProvider) override;

    // ITraceMessageSource
    void AddSink(extensions::ITraceMessageSink* sink) override;

    // IReplayDataProvider

    void ReplayMessage(const extensions::IReplayMessage* replayMessage) override;

private:
    //Private methods
    void ReplaySend(const extensions::IReplayMessage* replayMessage);
private:
    cfg::Replay _replayConfig;
    GenericPublisher _publisher;
};

} // namespace generic
} // namespace sim
} // namespace ib