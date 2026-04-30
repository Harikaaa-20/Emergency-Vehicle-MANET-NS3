/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Emergency Vehicle Priority System (FINAL WORKING VERSION)
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/aodv-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/wifi-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("EmergencyPrioritySystem");

int main(int argc, char *argv[])
{
    uint32_t numNodes = 10;
    double simTime = 30.0;

    // -------------------------------
    // Create Nodes
    // -------------------------------
    NodeContainer nodes;
    nodes.Create(numNodes);

    // -------------------------------
    // WiFi Setup
    // -------------------------------
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);

    YansWifiPhyHelper phy;
    YansWifiChannelHelper channel;

    channel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
    channel.AddPropagationLoss("ns3::FriisPropagationLossModel");

    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");

    NetDeviceContainer devices = wifi.Install(phy, mac, nodes);

    // -------------------------------
    // Mobility (FINAL FIXED)
    // -------------------------------
    MobilityHelper mobility;

    Ptr<RandomRectanglePositionAllocator> positionAlloc =
        CreateObject<RandomRectanglePositionAllocator>();

    positionAlloc->SetAttribute("X",
        StringValue("ns3::UniformRandomVariable[Min=0.0|Max=500.0]"));

    positionAlloc->SetAttribute("Y",
        StringValue("ns3::UniformRandomVariable[Min=0.0|Max=500.0]"));

    mobility.SetPositionAllocator(positionAlloc);

    mobility.SetMobilityModel("ns3::RandomWaypointMobilityModel",
        "Speed", StringValue("ns3::ConstantRandomVariable[Constant=10.0]"),
        "Pause", StringValue("ns3::ConstantRandomVariable[Constant=0.5]"),
        "PositionAllocator", PointerValue(positionAlloc));

    mobility.Install(nodes);

    // -------------------------------
    // AODV Routing
    // -------------------------------
    AodvHelper aodv;
    InternetStackHelper stack;
    stack.SetRoutingHelper(aodv);
    stack.Install(nodes);

    // -------------------------------
    // IP Addressing
    // -------------------------------
    Ipv4AddressHelper address;
    address.SetBase("10.0.0.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    uint16_t port = 9;

    // -------------------------------
    // 🚑 Emergency Traffic
    // -------------------------------
    OnOffHelper emergency("ns3::UdpSocketFactory",
        InetSocketAddress(interfaces.GetAddress(1), port));

    emergency.SetAttribute("DataRate", StringValue("5Mbps"));
    emergency.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer emergencyApp = emergency.Install(nodes.Get(0));
    emergencyApp.Start(Seconds(1.0));
    emergencyApp.Stop(Seconds(simTime));

    // -------------------------------
    // 🚗 Normal Traffic
    // -------------------------------
    OnOffHelper normal("ns3::UdpSocketFactory",
        InetSocketAddress(interfaces.GetAddress(1), port));

    normal.SetAttribute("DataRate", StringValue("1Mbps"));
    normal.SetAttribute("PacketSize", UintegerValue(512));

    ApplicationContainer normalApp = normal.Install(nodes.Get(2));
    normalApp.Start(Seconds(2.0));
    normalApp.Stop(Seconds(simTime));

    // -------------------------------
    // 📥 Receiver
    // -------------------------------
    PacketSinkHelper sink("ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), port));

    ApplicationContainer sinkApp = sink.Install(nodes.Get(1));
    sinkApp.Start(Seconds(0.0));
    sinkApp.Stop(Seconds(simTime));

    // -------------------------------
    // 🎥 Animation
    // -------------------------------
    AnimationInterface anim("animation.xml");

    anim.UpdateNodeDescription(nodes.Get(0), "Emergency 🚑");
    anim.UpdateNodeDescription(nodes.Get(1), "Receiver");
    anim.UpdateNodeDescription(nodes.Get(2), "Normal 🚗");

    anim.UpdateNodeColor(nodes.Get(0), 255, 0, 0);   // Red
    anim.UpdateNodeColor(nodes.Get(2), 0, 0, 255);   // Blue

    // -------------------------------
    // Flow Monitor
    // -------------------------------
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    monitor->SerializeToXmlFile("results.xml", true, true);

    Simulator::Destroy();

    return 0;
}
