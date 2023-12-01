// Function to print IP addresses of a node
void PrintNodeIPAddresses(Ptr<Node> node, std::string nodeName){
{
    Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
    for (uint32_t i = 1; i < ipv4->GetNInterfaces(); ++i)
    {
        Ipv4InterfaceAddress ifaceAddress = ipv4->GetAddress(i, 0);
        Ipv4Address ipAddress = ifaceAddress.GetLocal();
        std::cout << nodeName << " => node " << node->GetId() << " ==> IP address: " << ipAddress << std::endl;
    }
}

    // Désactiver toutes les interfaces du noeud

    Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();

    for (uint32_t i = 0; i < ipv4->GetNInterfaces(); i++) {

        ipv4->SetDown(i);

    }

    NS_LOG_DEBUG ("A t=2s, noeud en cours de désactivation ! ");

    Ipv4GlobalRoutingHelper::RecomputeRoutingTables();

    //



}
Simulator::Schedule(Seconds(2.5), &TurnOffNode, csmaNodes2.Get(0) // node libaghi ta9tal);
