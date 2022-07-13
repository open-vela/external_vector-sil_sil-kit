// ------------------------------------------------------------
// Slave 1 Setup (Sender)
LinControllerConfig slaveConfig;
slaveConfig.controllerMode = LinControllerMode::Slave;
slaveConfig.baudRate = 20000;

slave1->Init(slaveConfig);

// Register FrameStatusHandler to receive data
auto slave1_FrameStatusHandler = [](ILinController*, const LinFrameStatusEvent& frameStatusEvent) {
};
slave1->AddFrameStatusHandler(slave1_FrameStatusHandler);

// Setup a TX Response for LIN ID 0x11
LinFrame slave1Frame;
slave1Frame.id = 0x11;
slave1Frame.checksumModel = LinChecksumModel::Enhanced;
slave1Frame.dataLength = 8;
slave1Frame.data = {'S', 'L', 'A', 'V', 'E', '1', 0, 0};

slave1->SetFrameResponse(slave1Frame, LinFrameResponseMode::TxUnconditional);

// ------------------------------------------------------------
// Slave 2 Setup (Receiver)
LinControllerConfig slave2Config;
slave2Config.controllerMode = LinControllerMode::Slave;
slave2Config.baudRate = 20000;

slave2->Init(slave2Config);

// Register FrameStatusHandler to receive data
auto slave2_FrameStatusHandler = [](ILinController*, const LinFrameStatusEvent& frameStatusEvent) {
};
slave2->AddFrameStatusHandler(slave2_FrameStatusHandler);

// Setup LIN ID 0x11 as RX
LinFrame slave2Frame;
slave2Frame.id = 0x11;
slave2Frame.checksumModel = LinChecksumModel::Enhanced;
slave2Frame.dataLength = 8;

slave2->SetFrameResponse(slave2Frame, LinFrameResponseMode::Rx);

// ------------------------------------------------------------
// Master Setup
LinControllerConfig masterConfig;
masterConfig.controllerMode = LinControllerMode::Master;
masterConfig.baudRate = 20000;

master->Init(masterConfig);

// Register FrameStatusHandler to receive confirmation of the successful transmission
auto master_FrameStatusHandler = [](ILinController*, const LinFrameStatusEvent& frameStatusEvent) {
};
master->AddFrameStatusHandler(master_FrameStatusHandler);

// ------------------------------------------------------------
// Perform TX from slave to slave, i.e., slave1 provides the response, slave2 receives it.
if (UseAutosarInterface)
{
    // AUTOSAR API
    LinFrame frameRequest;
    frameRequest.id = 0x11;
    frameRequest.checksumModel = LinChecksumModel::Enhanced;

    master->SendFrame(frameRequest, LinFrameResponseType::SlaveToSlave);
}
else
{
    // alternative, non-AUTOSAR API

    // 1. setup the master response
    LinFrame frameRequest;
    frameRequest.id = 0x11;
    frameRequest.checksumModel = LinChecksumModel::Enhanced;
    master->SetFrameResponse(frameRequest, LinFrameResponseMode::Unused);

    // 2. transmit the frame header, the *slave* response will be transmitted automatically.
    master->SendFrameHeader(0x11);

    // Note: SendFrameHeader() can be called again without setting a new LinFrameResponse
}

// In both cases (AUTOSAR and non-AUTOSAR), the following callbacks will be triggered:
//  - TX confirmation for the master, who initiated the slave to slave transmission
master_FrameStatusHandler(master, LinFrameStatusEvent{timeEndOfFrame, slave1Frame, LinFrameStatus::LIN_TX_OK});
//  - TX confirmation for slave1, who provided the frame response
slave1_FrameStatusHandler(slave1, LinFrameStatusEvent{timeEndOfFrame, slave1Frame, LinFrameStatus::LIN_TX_OK});
//  - RX for slave2, who received the frame response
slave2_FrameStatusHandler(slave2, LinFrameStatusEvent{timeEndOfFrame, slave1Frame, LinFrameStatus::LIN_RX_OK});
