#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;
int
main (int argc, char *argv[])
{
  Config::SetDefault("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue(true));

// To DO
// how to satic route
// how to create ring topology with cmsa
// 
	//   
	// 
	// 
	// 


  NS_LOG_COMPONENT_DEFINE("log_ss_topo");
  uint16_t port_udp = 80;
  uint32_t n_lan1 = 1;
  uint32_t n_lan2 = 2;
  uint32_t n_cylcle = 4;
  // uint32_t maxBytes_tcp_1 = 1000;

  //////////////////////// Create Nodes ///////////////////////////////////
  /////////////////////////////////////////////////////////////////////////

    //For the cyclique netwrok 

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
  router_nodes.Create(3);

  Ptr<Node> r1 = router_nodes.Get(0);
  Ptr<Node> r2 = router_nodes.Get(1);
  Ptr<Node> r3 = router_nodes.Get(2);
  // include exluded nodes
  ////////////////////////////////////////////////////////////
  lan1_nodes.Add(r1);
  NS_LOG_INFO("Done : join r1 to LAN1 ");
  lan2_nodes.Add(r3);
  NS_LOG_INFO("Done : join r3 to LAN2 ");
  // joint an element of cycle_nodes to LAN1
  lan1_nodes.Add(lastnode_cycle);
  NS_LOG_INFO("Done : join lastnode_cycle to LAN1 ");
  NS_LOG_INFO("Done : nodes creation ");

  std::cout << "Netwrok Done" << std::endl;  
  //////////////////////// install links between devices ///////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////
  // ring lan1_devices

  PointToPointHelper p2p_cycle;
  p2p_cycle.SetDeviceAttribute("DataRate",StringValue("1Gbps"));
  p2p_cycle.SetChannelAttribute("Delay", TimeValue(NanoSeconds(2000)));
  
  NetDeviceContainer cycle_devices;

  cycle_devices = p2p_cycle.Install(node_0_cycle,node_1_cycle);
  cycle_devices.Add(p2p_cycle.Install(node_1_cycle,node_2_cycle));
  cycle_devices.Add(p2p_cycle.Install(node_2_cycle,lastnode_cycle));
  cycle_devices.Add(p2p_cycle.Install(lastnode_cycle,node_0_cycle));
 //   LAN1 Connection ///////////////////////////////////////////

  PointToPointHelper p2p_lan1;
  p2p_lan1.SetDeviceAttribute("DataRate",StringValue("1Gbps"));
  p2p_lan1.SetChannelAttribute("Delay", TimeValue(NanoSeconds(2500)));

  NetDeviceContainer lan1_devices;
  lan1_devices = p2p_lan1.Install(node_0_lan1,r1);
  lan1_devices = p2p_lan1.Install(lastnode_cycle,r1);
  NS_LOG_INFO("DONE : For  LAN 1");
 //   LAN2 Connection ///////////////////////////////////////////
  PointToPointHelper p2p_lan2;
  p2p_lan2.SetDeviceAttribute("DataRate",StringValue("1Gbps"));
  p2p_lan2.SetChannelAttribute("Delay", TimeValue(NanoSeconds(2500)));

  NetDeviceContainer lan2_devices_1;
  lan2_devices_1 = p2p_lan2.Install(node_0_lan2,r3);
  lan2_devices_1.Add(p2p_lan2.Install(node_1_lan2,r3));

  // NetDeviceContainer lan2_devices_2;
  // lan2_devices_2 = p2p_lan2.Install(node_1_lan2,r3);


  // lan2_devices = p2p_lan2.Install(node_0_lan2,node_1_lan2,r3);

  NS_LOG_INFO("DONE : For  LAN 2");
  // Connect The routers:
  //////////////////////////////////////////////////////////////////////
  //A PointToPoint connection between the two routers r1 and r2
  PointToPointHelper p2p_r1_r2;
  p2p_r1_r2.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p_r1_r2.SetChannelAttribute ("Delay", StringValue ("4ms"));

  PointToPointHelper p2p_r2_r3;
  p2p_r2_r3.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p_r2_r3.SetChannelAttribute ("Delay", StringValue ("4ms"));

  NetDeviceContainer firstHopLinkDevs;
  NetDeviceContainer secondHopLinkDevs;
  firstHopLinkDevs = p2p_r1_r2.Install (r1, r2);
  // 
  secondHopLinkDevs = p2p_r2_r3.Install (r2, r3);
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

  //For cycle topologie
  address.SetBase ("10.1.10.0", "255.255.255.0");
  Ipv4InterfaceContainer cyclelan_Interfaces;
  cyclelan_Interfaces = address.Assign (cycle_devices);

  //For LAN 1
  address.SetBase ("10.1.11.0", "255.255.255.0");
  Ipv4InterfaceContainer lan1_interfaces;
  lan1_interfaces = address.Assign (lan1_devices);
// id =0 -> node_0_lan1, id=1 -> r1 ;


  //For LAN 2
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer lan2_interfaces_1;
  lan2_interfaces_1 = address.Assign (lan2_devices_1) ;
  // ID=0 -> node_0_lan2,ID = 1 -> r3
  // Ipv4InterfaceContainer lan2_interfaces_2;
  // lan2_interfaces_2 = address.Assign (lan2_devices_2);
  // ID=0 -> r3,ID = 1 -> node_1_lan2




  //For PointToPoint link routers
  address.SetBase ("10.1.100.0", "255.255.255.0");
  Ipv4InterfaceContainer router_Interfaces;
  router_Interfaces = address.Assign (firstHopLinkDevs);
  // id=0 -> r1 , id=1 -> r2
  address.SetBase ("10.1.200.0", "255.255.255.0");
  Ipv4InterfaceContainer router_Interfaces2;
  router_Interfaces2 = address.Assign (secondHopLinkDevs);
  // id =0 -> r2 , id = 1 -> r3
  NS_LOG_INFO("Done : Assign address for all devices ");
  std::cout << "address assigned" << std::endl;  

    Ipv4Address ipaddress;
  ipaddress = r3->GetObject<Ipv4>()->GetAddress(3,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of r3 =" << ipaddress << std::endl; //

  ipaddress = r3->GetObject<Ipv4>()->GetAddress(2,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of r3 =" << ipaddress << std::endl; //

   ipaddress = r3->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of r3 =" << ipaddress << std::endl; //

   ipaddress = node_0_lan2->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of node_0_lan2 =" << ipaddress << std::endl; //

   ipaddress = node_1_lan2->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of node_1_lan2 =" << ipaddress << std::endl; //

  ipaddress = r2->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of r2 =" << ipaddress << std::endl; //
  ipaddress = r2->GetObject<Ipv4>()->GetAddress(2,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of r2 =" << ipaddress << std::endl; //

  ipaddress = r1->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(); // this line to get an address IP of a Node
  std::cout << "the adrress of r1 =" << ipaddress << std::endl; //

  ipaddress = lastnode_cycle->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(); // this line to get an address IP of a Node

  std::cout << "the adrress of lastnode_cycle =" << ipaddress << std::endl; //
  ipaddress = lastnode_cycle->GetObject<Ipv4>()->GetAddress(3,0).GetLocal(); // this line to get an address IP of a Node
  
  std::cout << "the adrress of lastnode_cycle =" << ipaddress << std::endl; //


  //////////////////////// install Application in devices ///////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////


  NS_LOG_INFO("start : UDP application with node_0_lan1 and node_0_lan2 ");

  //Let's install a UdpEchoServer on all nodes of LAN2
 // well-known echo port number
  UdpEchoServerHelper echoServer (port_udp);
  ApplicationContainer serverApp = echoServer.Install (NodeContainer(r1));
  serverApp.Start (Seconds (0));
  serverApp.Stop (Seconds (3));
  NS_LOG_INFO("Done : UDP server ");


  // For the Client node_0_LAN1_
  //Let's create UdpEchoClients in one LAN1's nodes.
  Ipv4Address ServerIPAddress;
  ServerIPAddress = r1->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();


  UdpEchoClientHelper echoClient (ServerIPAddress , port_udp); // (Address of r3, port_udp)
  echoClient.SetAttribute ("MaxPackets", UintegerValue (100));
  echoClient.SetAttribute ("Interval", TimeValue (MilliSeconds (200)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install(NodeContainer(node_0_lan2));
  clientApps.Start (Seconds (0));
  clientApps.Stop (Seconds (2));
  std::cout << "application  installed" << std::endl;  

  NS_LOG_INFO("Done : UDP clents ");
  // NS_LOG_INFO("Done : UDP application with node_0_lan1 and node_0_lan2 ");

  //////////////////////// Routing table ////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////


  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  p2p_lan2.EnablePcapAll("Devs");
  // p2p_r2_r3.EnablePcapAll("secondHopLinkDevs");
  // PcapHelper pcapHelper;
  // pcapHelper.EnablePcap("r3_tracing", r3, true, true);


Ptr<OutputStreamWrapper> routingStream =
        Create<OutputStreamWrapper>("dynamic-global-routing.routes", std::ios::out);
    Ipv4RoutingHelper::PrintRoutingTableAllAt(Seconds(6), routingStream);

  AnimationInterface anim("devices.xml");
  Simulator::Stop (Seconds (5));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;


  // lan1_devices = p2p_lan1.Install(lastnode_cycle,r1);
}