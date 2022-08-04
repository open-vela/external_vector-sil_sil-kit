/* Copyright (c) 2022 Vector Informatik GmbH

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include <chrono>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "NullConnectionParticipant.hpp"
#include "CanController.hpp"
#include "ConfigurationTestUtils.hpp"
#include "ParticipantConfiguration.hpp"

namespace {

using namespace SilKit::Core;
using namespace SilKit::Config;

class ParticipantTest : public testing::Test
{
protected:
    ParticipantTest()
    {
    }
};

TEST_F(ParticipantTest, throw_on_empty_participant_name)
{
    EXPECT_THROW(CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), ""),
                 SilKit::ConfigurationError);
}

TEST_F(ParticipantTest, support_nullptr_in_IParticipantConfiguration)
{
    EXPECT_NO_THROW(CreateNullConnectionParticipantImpl(nullptr, "TestParticipant"));
    EXPECT_NO_THROW(CreateNullConnectionParticipantImpl(std::make_shared<SilKit::Config::ParticipantConfiguration>(),
                                                        "TestParticipant"));
}

TEST_F(ParticipantTest, use_configured_name_on_participant_name_mismatch)
{
    const auto configuredParticipantName = "ConfiguredParticipantName";
    auto mockConfig = std::make_shared<SilKit::Config::ParticipantConfiguration>();
    mockConfig->participantName = configuredParticipantName;


    auto participant =
        CreateNullConnectionParticipantImpl(mockConfig, "TestParticipant");
    auto comParticipantName = participant->GetParticipantName();
    EXPECT_EQ(participant->GetParticipantName(), configuredParticipantName);
}

TEST_F(ParticipantTest, make_basic_controller)
{
    auto participant =
        CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), "TestParticipant");

    auto* canController = participant->CreateCanController("CAN1", "CAN1");
    auto basicCanController = dynamic_cast<SilKit::Services::Can::CanController*>(canController);

    EXPECT_NE(basicCanController, nullptr);
}

TEST_F(ParticipantTest, error_on_create_system_monitor_twice)
{
    auto participant =
        CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), "TestParticipant");

    EXPECT_NO_THROW(
        {
            try
            {
                participant->CreateSystemMonitor(); // ignore returned controller
            }
            catch (const std::exception&)
            {
                throw;
            }
        });

    EXPECT_THROW(
        {
            try
            {
                participant->CreateSystemMonitor(); // ignore returned controller
            }
            catch (const std::exception&)
            {
                throw;
            }
        },
        std::runtime_error);
}

TEST_F(ParticipantTest, error_on_create_system_controller_twice)
{
    auto participant =
        CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), "TestParticipant");

    EXPECT_NO_THROW({
        try
        {
            participant->CreateSystemController(); // ignore returned controller
        }
        catch (const std::exception&)
        {
            throw;
        }
    });

    EXPECT_THROW(
        {
            try
            {
                participant->CreateSystemController(); // ignore returned controller
            }
            catch (const std::exception&)
            {
                throw;
            }
        },
        std::runtime_error);
}

TEST_F(ParticipantTest, error_on_create_lifecycle_service_twice)
{
    auto participant =
        CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), "TestParticipant");

    EXPECT_NO_THROW({
        try
        {
            participant->CreateLifecycleService(
                {SilKit::Services::Orchestration::OperationMode::Coordinated}); // ignore returned controller
        }
        catch (const std::exception&)
        {
            throw;
        }
    });

    EXPECT_THROW(
        {
            try
            {
                participant->CreateLifecycleService(
                    {SilKit::Services::Orchestration::OperationMode::Coordinated}); // ignore returned controller
            }
            catch (const std::exception&)
            {
                throw;
            }
        },
        std::runtime_error);
}

TEST_F(ParticipantTest, no_error_on_get_logger_twice)
{
    auto participant =
        CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), "TestParticipant");

    EXPECT_NO_THROW({
        participant->GetLogger();
        participant->GetLogger();
    });
}

TEST_F(ParticipantTest, error_on_create_basic_controller_twice)
{
    auto participant =
        CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), "TestParticipant");

    participant->CreateCanController("CAN1", "CAN1");
    EXPECT_THROW(participant->CreateCanController("CAN1", "CAN1"), SilKit::ConfigurationError);
}


TEST_F(ParticipantTest, no_error_on_create_basic_controller_twice_different_network)
{
    auto participant =
        CreateNullConnectionParticipantImpl(SilKit::Config::MakeEmptyParticipantConfiguration(), "TestParticipant");

    auto* canController_can1 = participant->CreateCanController("CAN1", "CAN1");
    SilKit::Services::Can::ICanController* canController_can2;
    EXPECT_NO_THROW(canController_can2 = participant->CreateCanController("CAN1", "CAN2"));
    EXPECT_NE(canController_can1, nullptr);
    EXPECT_NE(canController_can2, nullptr);
    EXPECT_NE(canController_can1, canController_can2);
    
}

} // anonymous namespace