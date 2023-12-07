#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/trace-helper.h"
#include <ns3/mobility-module.h>
#include "ns3/flow-monitor-module.h"


using namespace ns3;
NS_LOG_COMPONENT_DEFINE("log_ss_topo");


// Function to print IP addresses of a node
void PrintNodeIPAddresses(Ptr<Node> node, std::string nodeName)
{
    Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
    for (uint32_t i = 1; i < ipv4->GetNInterfaces(); ++i)
    {
        Ipv4InterfaceAddress ifaceAddress = ipv4->GetAddress(i, 0);
        Ipv4Address ipAddress = ifaceAddress.GetLocal();
        std::cout << nodeName << " => node " << node->GetId() << " ==> IP address: " << ipAddress << std::endl;
    }
}

void TurnOffNode(Ptr<Node> node) {

    // Désactiver toutes les interfaces du noeud

    Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();

    for (uint32_t i = 0; i < ipv4->GetNInterfaces(); i++) {

        ipv4->SetDown(i);

    }






}
int
main (int argc, char *argv[])
{

  // create variable for each:
    // link
    // application
    // each address
    // 
  // how naming work 
    // use more naming 
  // 
  // simulate the fisrt scenario
  // Create More Problems
  // solve the firs Problem
  // NS configuration : ##############################################

  Config::SetDefault("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue(true));
  Config::SetDefault("ns3::Ipv4GlobalRouting::RandomEcmpRouting", BooleanValue(false));

  // Log enabling #####################################################
  Time::SetResolution(Time::NS);

  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  // LogComponentEnable("BulkSendApplication", LOG_LEVEL_INFO);
  // LogComponentEnable("PacketSink", LOG_LEVEL_INFO);
  // LogComponentEnable("log_ss_topo", LOG_LEVEL_INFO);



  CommandLine cmd(__FILE__);
  cmd.Parse(argc, argv);


 // flow monitoring variables variables ###########################################
  // uint32_t SentPackets = 0;
  // uint32_t ReceivedPackets = 0;
  // uint32_t LostPackets = 0;


 // creation Node variables ###########################################
  uint32_t n_lan1 = 1;
  uint32_t n_lan2 = 2;
  uint32_t n_cylcle = 4;
  // uint32_t maxBytes_tcp_1 = 1000;
  // uint32_t maxBytes_tcp_2 = 1000;
  // links variables ###################################################
          //###################################################
    // ring LAN links :
      // Device Attribute :
  StringValue p2p_cycle_DataRate = StringValue("1Mbps"); // how much data will generate per second
  TimeValue p2p_cycle_InterframeGap = TimeValue(NanoSeconds(0)) ; // = 0
  StringValue p2p_cycle_MTU = StringValue("1500") ; // = 1500
  // Ptr<ErrorModel> p2p_cycle_REM = ; // 0
  // Ptr<Queue<Packet>> p2p_cycle_TxQ = ; //0
      // Channel Attribute :
  TimeValue p2p_cycle_Delay = TimeValue(MilliSeconds(5)) ; // = 0

          //###################################################
    //  LAN1 links :
      // Device Attribute :
  StringValue p2p_lan1_DataRate = StringValue("0.5Mbps"); // how much data will generate per second
  TimeValue p2p_lan1_InterframeGap = TimeValue(NanoSeconds(0)); // = 0
  StringValue p2p_lan1_MTU = StringValue("1500") ; // = 1500
  // Ptr<ErrorModel> p2p_lan1_REM = ; // 0
  // Ptr<Queue<Packet>> p2p_lan1_TxQ = 100 ; //0
      // Channel Attribute :
  TimeValue p2p_lan1_Delay = TimeValue(MilliSeconds(5)) ; // = 0

          //###################################################
    //  LAN2 links :
      // Device Attribute :
  StringValue p2p_lan2_DataRate = StringValue("1Mbps"); // how much data will generate per second
  TimeValue p2p_lan2_InterframeGap = TimeValue(NanoSeconds(0)); // = 0
  StringValue p2p_lan2_MTU = StringValue("1500") ; // = 1500
  // Ptr<ErrorModel> p2p_lan2_REM = ; // 0
  // Ptr<Queue<Packet>> p2p_lan2_TxQ = ; //0
      // Channel Attribute :
  TimeValue p2p_lan2_Delay = TimeValue(MilliSeconds(5)) ; // = 0

          //###################################################
    //  From R1 to R2 links :
      // Device Attribute :
  StringValue p2p_r1r2_DataRate = StringValue("2.5Mbps"); // how much data will generate per second
  TimeValue p2p_r1r2_InterframeGap = TimeValue(NanoSeconds(0)); // = 0
  StringValue p2p_r1r2_MTU = StringValue("1500") ; // = 1500
  // Ptr<ErrorModel> p2p_r1r2_REM = ; // 0
  // Ptr<Queue<Packet>> p2p_r1r2_TxQ = ; //0
      // Channel Attribute :
  TimeValue p2p_r1r2_Delay = TimeValue(MilliSeconds(12)) ; // = 0

          //###################################################
        //  From R1 to R2 links :
      // Device Attribute :
  StringValue p2p_r2r3_DataRate = StringValue("2.5Mbps"); // how much data will generate per second
  TimeValue p2p_r2r3_InterframeGap = TimeValue(NanoSeconds(0)); // = 0
  StringValue p2p_r2r3_MTU = StringValue("1500") ; // = 1500
  // Ptr<ErrorModel> p2p_r2r3_REM = ; // 0
  // Ptr<Queue<Packet>> p2p_r2r3_TxQ = ; //0
      // Channel Attribute :
  TimeValue p2p_r2r3_Delay = TimeValue(MilliSeconds(12)); // = 0



  // Applications variables ###################################################

  // uint32_t maxBytes_tcp_1 = 1000;
  // uint32_t maxBytes_tcp_2 = 4000;

  //////////////////////// Create Nodes ///////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

    //For the cyclique netwrok 
  std::cout << "Network start" << std::endl;  
  NodeContainer cycle_nodes;
  cycle_nodes.Create(n_cylcle);
  Ptr<Node> node_0_cycle = cycle_nodes.Get(0);
  Ptr<Node> node_1_cycle = cycle_nodes.Get(1);
  Ptr<Node> node_2_cycle = cycle_nodes.Get(2);
  Ptr<Node> lastnode_cycle = cycle_nodes.Get(3);
  
  NS_LOG_INFO("Done : cycle nodes creation ");


  //For the first network
  NS_LOG_INFO("start : nodes creation ");

  NodeContainer lan1_nodes;
  lan1_nodes.Create(n_lan1);
  Ptr<Node> node_0_lan1 = lan1_nodes.Get(0);
  NS_LOG_INFO("Done : LAN1 node creation ");
  
   //For the second network

  NodeContainer lan2_nodes;
  lan2_nodes.Create(n_lan2);
  Ptr<Node> node_0_lan2 = lan2_nodes.Get(0);
  Ptr<Node> node_1_lan2 = lan2_nodes.Get(1);
  NS_LOG_INFO("Done : LAN2 nodes creation ");




  // creation of routers :
  NodeContainer router_nodes;
  router_nodes.Create(4);

  Ptr<Node> r1 = router_nodes.Get(0);
  Ptr<Node> r2 = router_nodes.Get(1);
  Ptr<Node> r3 = router_nodes.Get(2);
  Ptr<Node> r4 = router_nodes.Get(3);
  // include exluded nodes
  ////////////////////////////////////////////////////////////
  lan1_nodes.Add(r1);
  lan1_nodes.Add(r4);
  NS_LOG_INFO("Done : join r1 to LAN1 ");
  lan2_nodes.Add(r3);
  NS_LOG_INFO("Done : join r3 to LAN2 ");
  // joint an element of cycle_nodes to LAN1
  lan1_nodes.Add(lastnode_cycle);
  NS_LOG_INFO("Done : join lastnode_cycle to LAN1 ");


  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install(cycle_nodes);
  mobility.Install(router_nodes);
  mobility.Install(lan1_nodes);
  mobility.Install(lan2_nodes);

  NS_LOG_INFO("Done : nodes creation ");

  std::cout << "Netwrok Done" << std::endl;  
  //////////////////////// install links between devices ///////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////
  // ring lan1_devices
  std::cout << "links between devices start" << std::endl;  

 

  PointToPointHelper p2p_cycle;
  p2p_cycle.SetDeviceAttribute("DataRate",p2p_cycle_DataRate);
  p2p_cycle.SetDeviceAttribute("Mtu", p2p_cycle_MTU); // =1500
  p2p_cycle.SetDeviceAttribute("InterframeGap", p2p_cycle_InterframeGap); 
  // p2p_cycle.SetDeviceAttribute("ReceiveErrorModel", );
  
  // p2p_cycle.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("1p"));

  p2p_cycle.SetChannelAttribute("Delay", p2p_cycle_Delay); 

  
  NetDeviceContainer cycle_dev_01 = p2p_cycle.Install(node_0_cycle,node_1_cycle);
  NetDeviceContainer cycle_dev_12 = p2p_cycle.Install(node_1_cycle,node_2_cycle);
  NetDeviceContainer cycle_dev_23 = p2p_cycle.Install(node_2_cycle,lastnode_cycle);
  NetDeviceContainer cycle_dev_30 = p2p_cycle.Install(lastnode_cycle,node_0_cycle);
 //   LAN1 Connection ///////////////////////////////////////////


  PointToPointHelper p2p_lan1;
  p2p_lan1.SetDeviceAttribute("DataRate",p2p_lan1_DataRate);

  p2p_lan1.SetDeviceAttribute("Mtu", p2p_lan1_MTU); // =1500
  p2p_lan1.SetDeviceAttribute("InterframeGap", p2p_lan1_InterframeGap); 
  // p2p_lan1.SetDeviceAttribute("ReceiveErrorModel", );
  
  // p2p_lan1.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("50p"));

  p2p_lan1.SetChannelAttribute("Delay", p2p_lan1_Delay);

// ####################################################################### //
// ####################################################################### //

  PointToPointHelper p2p_lan1_c4r1;
  p2p_lan1_c4r1.SetDeviceAttribute("DataRate",StringValue("2Mbps"));
  p2p_lan1_c4r1.SetChannelAttribute("Delay", TimeValue(p2p_lan1_Delay));
  // p2p_lan1_c4r1.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("1p"));




  NetDeviceContainer lan1_dev_n0r1 = p2p_lan1.Install(node_0_lan1,r1);


  NetDeviceContainer lan1_dev_c4r1 = p2p_lan1_c4r1.Install(lastnode_cycle,r1);

  NetDeviceContainer lan1_dev_c1r4 = p2p_lan1_c4r1.Install(node_2_cycle,r4);
  NS_LOG_INFO("DONE : For  LAN 1");


 //   LAN2 Connection ///////////////////////////////////////////


  PointToPointHelper p2p_lan2_n1r3;
  p2p_lan2_n1r3.SetDeviceAttribute("DataRate", p2p_lan2_DataRate);
  p2p_lan2_n1r3.SetDeviceAttribute("Mtu", p2p_lan2_MTU); // =1500
  p2p_lan2_n1r3.SetDeviceAttribute("InterframeGap", p2p_lan2_InterframeGap); 
  // p2p_lan2_n1r3.SetDeviceAttribute("ReceiveErrorModel", );

  // p2p_lan2_n1r3.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("50p"));

  p2p_lan2_n1r3.SetChannelAttribute("Delay", p2p_lan2_Delay);


  PointToPointHelper p2p_lan2_n0r3;
  p2p_lan2_n0r3.SetDeviceAttribute("DataRate", p2p_lan2_DataRate);
  p2p_lan2_n0r3.SetDeviceAttribute("Mtu", p2p_lan2_MTU); // =1500
  p2p_lan2_n0r3.SetDeviceAttribute("InterframeGap", p2p_lan2_InterframeGap); 
  // p2p_lan2_n0r3.SetDeviceAttribute("ReceiveErrorModel", );

  // p2p_lan2_n0r3.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("50p"));

  p2p_lan2_n0r3.SetChannelAttribute("Delay", p2p_lan2_Delay);

  NetDeviceContainer lan2_dev_n0r3 = p2p_lan2_n0r3.Install(node_0_lan2,r3);
  NetDeviceContainer lan2_dev_n1r3 = p2p_lan2_n1r3.Install(node_1_lan2,r3);


  NS_LOG_INFO("DONE : For  LAN 2");
  // Connect The routers:
  //////////////////////////////////////////////////////////////////////
  //A PointToPoint connection between the two routers r1 and r2


  PointToPointHelper p2p_r1_r2;
  p2p_r1_r2.SetDeviceAttribute("DataRate", p2p_r1r2_DataRate);
  p2p_r1_r2.SetDeviceAttribute("Mtu", p2p_r1r2_MTU); // =1500
  p2p_r1_r2.SetDeviceAttribute("InterframeGap", p2p_r1r2_InterframeGap); 

  // p2p_r1_r2.SetDeviceAttribute("ReceiveErrorModel", );

  // p2p_r1_r2.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("50p"));

  p2p_r1_r2.SetChannelAttribute("Delay", p2p_r1r2_Delay);

  PointToPointHelper p2p_r2_r3;
  p2p_r2_r3.SetDeviceAttribute("DataRate", p2p_r2r3_DataRate);
  p2p_r2_r3.SetDeviceAttribute("Mtu", p2p_r2r3_MTU); // =1500
  p2p_r2_r3.SetDeviceAttribute("InterframeGap", p2p_r2r3_InterframeGap); 
// p2p_r2_r3.SetDeviceAttribute("ReceiveErrorModel", );



  // p2p_r2_r3.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("50p"));

  p2p_r2_r3.SetChannelAttribute("Delay", p2p_r2r3_Delay);


  PointToPointHelper p2p_r2_r4;
  p2p_r2_r4.SetDeviceAttribute("DataRate", p2p_r2r3_DataRate);
  p2p_r2_r4.SetDeviceAttribute("Mtu", p2p_r2r3_MTU); // =1500
  p2p_r2_r4.SetDeviceAttribute("InterframeGap", p2p_r2r3_InterframeGap); 
// p2p_r2_r4.SetDeviceAttribute("ReceiveErrorModel", );

  

  // p2p_r2_r3.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("50p"));
TimeValue p2p_r2r4_Delay = TimeValue(MilliSeconds(5)) ;
  p2p_r2_r4.SetChannelAttribute("Delay", p2p_r2r4_Delay);


  NetDeviceContainer Dev_r1r2 = p2p_r1_r2.Install (r1, r2);

  NetDeviceContainer Dev_r2r4 = p2p_r2_r4.Install (r2, r4);


  NetDeviceContainer Dev_r2r3 = p2p_r2_r3.Install (r2, r3);
  
  // 
  
  // 
  std::cout << "Links Done" << std::endl;  

  NS_LOG_INFO("DONE : For  bettween r1 and r2");

  //A PointToPoint connection between the two routers r2 and r3

  // NetDeviceContainer secondHopLinkDevs;
  // secondHopLinkDevs = p2p_r2_r3.Install (r2, r3);

  NS_LOG_INFO("DONE : For  bettween r2 and r3");

  NS_LOG_INFO("Done : create links ");


  
  //////////////////////// assign address' /////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////


  InternetStackHelper stack;
  stack.InstallAll();

  Ipv4AddressHelper address;

  // For cycle topologie
  address.SetBase ("8.0.1.0", "255.255.255.252");
  Ipv4InterfaceContainer ring_Int_01 = address.Assign (cycle_dev_01);
  address.SetBase ("8.1.2.0", "255.255.255.252");
  Ipv4InterfaceContainer ring_Int_12 = address.Assign (cycle_dev_12);
  address.SetBase ("8.2.3.0", "255.255.255.252");
  Ipv4InterfaceContainer ring_Int_23 = address.Assign (cycle_dev_23);
  address.SetBase ("8.3.0.0", "255.255.255.252");
  Ipv4InterfaceContainer ring_Int_30 = address.Assign (cycle_dev_30);

  //For LAN 1
  address.SetBase ("10.0.1.0", "255.255.255.252");
  Ipv4InterfaceContainer lan1_int_n0r1 = address.Assign (lan1_dev_n0r1);
  address.SetBase ("10.8.1.0", "255.255.255.252");
  Ipv4InterfaceContainer lan1_int_c4r1 = address.Assign (lan1_dev_c4r1);

    address.SetBase ("10.8.4.0", "255.255.255.252");
  Ipv4InterfaceContainer lan1_int_c1r4 = address.Assign (lan1_dev_c1r4);

  // id =0 -> node_0_lan1, id=1 -> r1 ;


  //For LAN 2
  address.SetBase ("10.0.3.0", "255.255.255.0");
  Ipv4InterfaceContainer lan2_int_n0r3 = address.Assign (lan2_dev_n0r3) ;
  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer lan2_int_n1r3 = address.Assign (lan2_dev_n1r3) ;

  // ID=0 -> node_0_lan2,ID = 1 -> r3
  // ID=0 -> r3,ID = 1 -> node_1_lan2




  // //For PointToPoint link routers
  address.SetBase ("100.1.2.0", "255.255.255.252");
  Ipv4InterfaceContainer router_Interfaces;
  router_Interfaces = address.Assign (Dev_r1r2);
  // id=0 -> r1 , id=1 -> r2
  address.SetBase ("100.2.3.0", "255.255.255.252");
  Ipv4InterfaceContainer router_Interfaces2;
  router_Interfaces2 = address.Assign (Dev_r2r3);

  address.SetBase ("100.2.4.0", "255.255.255.252");
  Ipv4InterfaceContainer router_Interfaces3;
  router_Interfaces3 = address.Assign (Dev_r2r4);
  // id =0 -> r2 , id = 1 -> r3
  NS_LOG_INFO("Done : Assign address for all devices ");
  std::cout << "address assigned" << std::endl;  

  // PrintNodeIPAddresses(node_0_lan1, "node_0_lan1");
  // PrintNodeIPAddresses(lastnode_cycle, "lastnode_cycle");
  // PrintNodeIPAddresses(node_0_cycle, "node_0_cycle");
  // PrintNodeIPAddresses(node_1_cycle, "node_1_cycle");
  // PrintNodeIPAddresses(node_2_cycle, "node_2_cycle");
  // PrintNodeIPAddresses(node_0_lan2, "node_0_lan2");
  // PrintNodeIPAddresses(node_1_lan2, "node_1_lan2");
  // PrintNodeIPAddresses(r2, "r2");
  // PrintNodeIPAddresses(r3, "r3");
  // PrintNodeIPAddresses(r1, "r1");


  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  //////////////////////// install Application in devices ///////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////
///////////// UDP echo Application server and client ///////////// ////////////////////


  NS_LOG_INFO("start : UDP Echo application with node_0_lan1 and node_0_lan2 ");

  // uint16_t port_udp = 40;
  // Ptr<Node> server_UDP_Echo = node_0_cycle;
  // Ptr<Node> client_UDP_Echo = node_0_lan2;
  int TimeValue_ms = 10 ;
    // uint32_t maxPacketCount_UDP_echo = 0; // max packets the application will ssent
    // Time interPacketInterval_UDP_echo = MilliSeconds(TimeValue_ms);
    // uint32_t MaxPacketSize_UDP_echo = 0; //byte , 1MB = 1024 * 1024  B
  // minmum in this packet size is = 20 Bytes (txheaderSize)
  // std::cout << "Supposed Throughput of UdpEchoClient Application :\n  Throughput = " << (double)(MaxPacketSize_UDP_Echo*8) / (TimeValue_ms * 1024) << "Mbps" << std::endl;  


  // UdpEchoServerHelper echoServer (port_udp);
  // ApplicationContainer serverApp = echoServer.Install (NodeContainer(server_UDP_Echo));
  // serverApp.Start (Seconds (0));
  // serverApp.Stop (Seconds (1));
  // NS_LOG_INFO("Done : UDP server ");  


  // // For the Client node_0_LAN1 
  // // Let's create UdpEchoClients in one LAN1's nodes.
  // Ipv4Address UDPServerIPAddress_Echo;
  // UDPServerIPAddress_Echo = server_UDP_Echo->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();


  // UdpEchoClientHelper echoClient (UDPServerIPAddress_Echo , port_udp); // (Address of r3, port_udp)
  // echoClient.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount_UDP_echo)); // maximum number of packet that can be sent
  // echoClient.SetAttribute ("Interval", TimeValue (interPacketInterval_UDP_echo)); // time to wait between intervale
  // echoClient.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize_UDP_echo)); // in byte a suppose

  // ApplicationContainer clientApps = echoClient.Install(NodeContainer(client_UDP_Echo));
  // clientApps.Start (Seconds (0));
  // clientApps.Stop (Seconds (1));
  // std::cout << "application  installed" << std::endl;  

  NS_LOG_INFO("Done : UDP clents ");
  NS_LOG_INFO("Done : UDP application with node_0_lan1 and node_0_lan2 ");

///////////// UDP Application server and client ///////////// ////////////////////

    uint16_t port_udp_2 = 4000;
    Ptr<Node> server_UDP = node_1_cycle;
    Ptr<Node> client_UDP = node_0_lan2;
    Ipv4Address UDPServerIPAddress = server_UDP->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
    TimeValue_ms = 10;
    uint32_t MaxPacketSize_UDP = 900; // the minimum size = txheaderSize = 12 

    // the size above do not include the header packets ? what is this extra 28 byte in each packet
    Time interPacketInterval_UDP = MilliSeconds(TimeValue_ms);
    uint32_t maxPacketCount_UDP = 0;

    std::cout << "Supposed Throughput of UdpEchoClient Application :\n  DataRate = " << ((double)(MaxPacketSize_UDP) * 8) / (TimeValue_ms * 1024 * 1024 /1000) << " Mbps" << std::endl;  

    NS_LOG_INFO("Create UdpServer application on node 1.");




    UdpServerHelper server(port_udp_2);
    ApplicationContainer apps = server.Install(server_UDP);
    apps.Start(Seconds(1.0));
    apps.Stop(Seconds(10.0));

    NS_LOG_INFO("Create UdpClient application on node 0 to send to node 1.");

    UdpClientHelper client(UDPServerIPAddress, port_udp_2);
    client.SetAttribute("MaxPackets", UintegerValue(maxPacketCount_UDP));
    client.SetAttribute("Interval", TimeValue(interPacketInterval_UDP));
    client.SetAttribute("PacketSize", UintegerValue(MaxPacketSize_UDP));
    apps = client.Install(client_UDP);
    apps.Start(Seconds(2.0));
    apps.Stop(Seconds(8.0));

///////////// UDP Application server and client 2 ///////////// ////////////////////

    // uint16_t port_udp = 300;
    // Ptr<Node> server_UDP_2 = node_2_cycle;
    // Ptr<Node> client_UDP_2 = node_0_lan2;
    // Ipv4Address UDPServerIPAddress_2 = server_UDP_2->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
    // TimeValue_ms = 10;
    // uint32_t MaxPacketSize_UDP_2 = 1220; // the minimum size = txheaderSize = 12 
    // // the size above do not include the header packets ? what is this extra 28 byte in each packet
    // Time interPacketInterval_UDP_2 = MilliSeconds(TimeValue_ms);
    // uint32_t maxPacketCount_UDP_2 = 0;

    // std::cout << "Supposed DataRate of UdpEchoClient Application 2 :\n  DataRate = " << ((double)(MaxPacketSize_UDP_2) * 8) / (TimeValue_ms * 1024 * 1024 /1000) << " Mbps" << std::endl;  

    // NS_LOG_INFO("Create UdpServer application on node 1.");




    // UdpServerHelper server_2(port_udp);
    // ApplicationContainer apps_2 = server_2.Install(server_UDP_2);
    // apps_2.Start(Seconds(1.0));
    // apps_2.Stop(Seconds(10.0));

    // NS_LOG_INFO("Create UdpClient application on node 0 to send to node 1.");

    // UdpClientHelper client_2(UDPServerIPAddress_2, port_udp);
    // client_2.SetAttribute("MaxPackets", UintegerValue(maxPacketCount_UDP_2));
    // client_2.SetAttribute("Interval", TimeValue(interPacketInterval_UDP_2));
    // client_2.SetAttribute("PacketSize", UintegerValue(MaxPacketSize_UDP_2));
    // apps_2 = client_2.Install(client_UDP_2);
    // apps_2.Start(Seconds(3.0));
    // apps_2.Stop(Seconds(9.0));


///////////// TCP Application the fisrt one ///////////// ////////////////////
  // of the client
  NS_LOG_INFO("start : TCP application with node_0_cycle and node_2_cycle ");
    // uint16_t port_tcp_1 = 9; // well-known echo port number
    // Ptr<Node> source_TCP_1 = node_0_cycle;
    // Ptr<Node> sink_TCP_1 = node_2_cycle;


    // Ipv4Address TCP1SourceIP,TCP1SinkerIP;
    // TCP1SourceIP = source_TCP_1->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
    // TCP1SinkerIP = sink_TCP_1->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();

  //     BulkSendHelper source_1("ns3::TcpSocketFactory", InetSocketAddress(TCP1SinkerIP, port_tcp_1));
  //     // Set the amount of data to send in bytes.  Zero is unlimited.
  //     source_1.SetAttribute("MaxBytes", UintegerValue(maxBytes_tcp_1));
  //     ApplicationContainer sourceApps_1 = source_1.Install(NodeContainer(node_0_cycle));
  //     sourceApps_1.Start(Seconds(2));
  //     sourceApps_1.Stop(Seconds(3));

  // // of the server
  //     PacketSinkHelper sink_1("ns3::TcpSocketFactory", InetSocketAddress(TCP1SourceIP, port_tcp_1));
  //         ApplicationContainer sinkApps_1 = sink_1.Install(NodeContainer(node_2_cycle));
  //         sinkApps_1.Start(Seconds(2.0));
  //         sinkApps_1.Stop(Seconds(5.0));
  NS_LOG_INFO("Done : TCP application with node_0_cycle and node_2_cycle ");

  ///////////// TCP Application the second one 
  // of the client
  NS_LOG_INFO("start : TCP application with node_0_cycle and node_2_cycle ");

  //   uint16_t port_tcp_2 = 10; 
  //   Ipv4Address TCP2SourceIP,TCP2SinkerIP;
  //   Ptr<Node> source_TCP_2 = node_1_cycle;
  //   Ptr<Node> sink_TCP_2 = node_1_lan2;


  //   TCP2SourceIP = source_TCP_2->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
  //   TCP2SinkerIP = sink_TCP_2->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();

  //     BulkSendHelper source_2("ns3::TcpSocketFactory", InetSocketAddress(TCP2SinkerIP, port_tcp_2));
  //     // Set the amount of data to send in bytes.  Zero is unlimited.
  //     source_2.SetAttribute("MaxBytes", UintegerValue(maxBytes_tcp_1));
  //     // source_2.SetAttribute("SendSize", UintegerValue(maxBytes_tcp_2/4));

  //     ApplicationContainer sourceApps_2 = source_2.Install(NodeContainer(source_TCP_2));
  //     sourceApps_2.Start(Seconds(5.0));
  //     sourceApps_2.Stop(Seconds(7.0));

  // // of the server
  //     PacketSinkHelper sink_2("ns3::TcpSocketFactory", InetSocketAddress(TCP2SourceIP, port_tcp_2));
  //         ApplicationContainer sinkApps_2 = sink_2.Install(NodeContainer(sink_TCP_2));
  //         sinkApps_2.Start(Seconds(5.0));
  //         sinkApps_2.Stop(Seconds(8.0));

  NS_LOG_INFO("start : TCP application with node_0_cycle and node_2_cycle ");
  NS_LOG_INFO("start : copyrun ");


  //////////////////////// Routing table ////////////////////////////////////////////
  //////////////////////// Flow monitoring  ////////////////////////////////////////////
FlowMonitorHelper flow_monitorHelper;
Ptr<FlowMonitor> monitor =flow_monitorHelper.InstallAll();
monitor->SetAttribute("DelayBinWidth", DoubleValue(0.001));
monitor->SetAttribute("JitterBinWidth", DoubleValue(0.001));
monitor->SetAttribute("PacketSizeBinWidth", DoubleValue(20));


  //////////////////////////////////////////////////////////////////////////////////////////


  // p2p_lan2_n0r3.EnablePcap("Devs_lan2", lan2_nodes.Get() );
  // p2p_lan2_n1r3.EnablePcap("Devs_lan1", node_1_lan2  ->GetId(), 0);
  // p2p_lan1.EnablePcapInternal("Devs", lan1_dev_n0r1.Get(1), true, true);
  // p2p_r2_r3.EnablePcapAll("secondHopLinkDevs");
// Simulator::Schedule(Seconds(0.5),bul &Ipv4GlobalRoutingHelper::RecomputeRoutingTables);
// Ptr<OutputStreamWrapper> routingStream =
//         Create<OutputStreamWrapper>("dynamic-global-routing.routes", std::ios::out);
//     Ipv4RoutingHelper::PrintRoutingTableAllAt(Seconds(6), routingStream);



  AnimationInterface anim("Animation_Test.xml");
    anim.SetConstantPosition (node_0_cycle  , 56.00 , 66.00 );// id=0 
    anim.SetConstantPosition (node_1_cycle  , 48.00 , 76.00 );// id=1
    anim.SetConstantPosition (node_2_cycle  , 39.00 , 66.00 );// id=2
    anim.SetConstantPosition (lastnode_cycle, 48.00 , 55.00 );// id=3
    anim.SetConstantPosition (node_0_lan1   , 8.00  , 66.00 );// id=4
    anim.SetConstantPosition (node_0_lan2   , 62.00 , 5.00 );// id=5
    anim.SetConstantPosition (node_1_lan2   , 11.00 , 6.00 );// id=6
    anim.SetConstantPosition (r1            , 39.00 , 52.00 );// id=7
    anim.SetConstantPosition (r2            , 39.00 , 33.00 );// id=8
    anim.SetConstantPosition (r3            , 39.00 , 17.00 );// id=9
    anim.SetConstantPosition (r4            , 30.00 , 53.00 );// id=10

  //   anim.EnablePacketMetadata(true);

Simulator::Schedule(Seconds(2.5), &TurnOffNode, node_2_cycle );

  Simulator::Stop (Seconds (10));
  Simulator::Run ();


// setting up packet flow monitoring
  monitor->CheckForLostPackets();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flow_monitorHelper.GetClassifier());
  FlowMonitor::FlowStatsContainer stats = monitor->GetFlowStats();

  uint32_t packetLost = 0.0;
  uint32_t totalTxPackets = 0.0;

  double averageFlowThroughput = 0.0;
  double averageFlowDelay = 0.0;

  double flowDuration = 6;

  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin(); i != stats.end(); ++i) {
    Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
    flowDuration = i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds() ;

    std::stringstream protoStream;
    protoStream << (uint16_t)t.protocol;
    // if (t.protocol == 17) {
    //   protoStream.str("UDP");
    // }

    std::cout << "Flow " << i->first << " (" << t.sourceAddress << ":" << t.sourcePort << " -> " << t.destinationAddress << ":" << t.destinationPort << ") proto " << protoStream.str() << "\n";

    packetLost += (i->second.txPackets - i->second.rxPackets);
    totalTxPackets += i->second.txPackets;

    if (i->second.rxPackets > 0) {
      averageFlowThroughput += (i->second.rxBytes - i->second.rxPackets * 28 )  * 8.0 / flowDuration / 1024 / 1024;
      averageFlowDelay += 1000 * i->second.delaySum.GetSeconds() / i->second.rxPackets;

      // std::cout << "  Rxbytes: " << (double)i-> second.rxBytes / 1024 / 1024<< " MB \n" << std::endl;
      std::cout << "  rxPackets: " << (double)i-> second.rxPackets << " p \n" << std::endl;
      // std::cout << "  BytesPerPacket: " << (double)i-> second.txBytes  /(double)i-> second.txPackets << " Bpp \n" << std::endl;
      std::cout << "  txPackets: " << (double)i->second.txPackets << " p \n" << std::endl;
      // std::cout << "  True Txbytes: " << (double)i->second.txBytes - i->second.txPackets*28    << " B \n" << std::endl;

      std::cout << "  Throughput: " <<  (i->second.rxBytes - i->second.rxPackets * 28 )  * 8 / flowDuration / 1024 / 1024 << " Mbps\n" << std::endl; // with 28 is the size of the header of the udp echo packets

      std::cout << "  Loss Rate: " << 100 * ((double)i->second.txPackets - (double)i->second.rxPackets) / (double)i->second.txPackets << " %\n" << std::endl;
      std::cout << "  Delay: " << 1000 * i->second.delaySum.GetSeconds() / i->second.rxPackets << " ms\n\n" << std::endl;
    }
    else {
      std::cout << "  Throughput: 0 Mbps\n" << std::endl;
      std::cout << "  Loss Rate: 100%\n" << std::endl;
      std::cout << "  Delay: 0 ms\n\n" << std::endl;        
    }
  }

  // extracting average packet flow data
  // std::cout << "\nMean Flow Throughput: " << averageFlowThroughput / stats.size() << " Mbps\n" << std::endl;
  // std::cout << "Mean Packet Loss Rate: " << 100 * (double)packetLost / (double)totalTxPackets << " %\n" << std::endl;
  // std::cout << "Mean Flow Delay: " << averageFlowDelay / stats.size() << " ms\n" << std::endl;

  // outFile.close();

  // std::ifstream f(filename.c_str());
  // if (f.is_open()) {
  //   std::cout << f.rdbuf();
  // }
  // monitor->SerializeToXmlFile("ss_topologie.xml", true , true);
  Simulator::Destroy ();
  return 0;

}