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
