void TurnOffNode(Ptr<Node> node) {

    // Désactiver toutes les interfaces du noeud

    Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();

    for (uint32_t i = 0; i < ipv4->GetNInterfaces(); i++) {

        ipv4->SetDown(i);

    }

    NS_LOG_DEBUG ("A t=2s, noeud en cours de désactivation ! ");

    Ipv4GlobalRoutingHelper::RecomputeRoutingTables();

    //



}
