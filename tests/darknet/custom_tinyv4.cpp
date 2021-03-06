#include<iostream>
#include<vector>
#include "tkdnn.h"
#include "test.h"
#include "DarknetParser.h"

int main() {
    std::string bin_path  = "../../darknet_tinyv4";
    std::string cfg_base = "../..";
    std::vector<std::string> input_bins = {
        bin_path + "/layers/input.bin"
    };

    std::vector<std::string> output_bins = {
        bin_path + "/debug/layer30_out.bin",
        bin_path + "/debug/layer37_out.bin"
    };

    std::string wgs_path  = bin_path + "/layers";
    std::string cfg_path  = cfg_base + "/tinv4_multi.cfg";
    std::string name_path = cfg_base + "/obj.names";
    std::cout << cfg_path << std::endl;
    std::cout << name_path << std::endl;

    // parse darknet network
    tk::dnn::Network *net = tk::dnn::darknetParser(cfg_path, wgs_path, name_path);
    net->print();

    //convert network to tensorRT
    tk::dnn::NetworkRT *netRT = new tk::dnn::NetworkRT(net, net->getNetworkRTName("custom_tinyv4_nano"));

    int ret = testInference(input_bins, output_bins, net, netRT);
    net->releaseLayers();
    delete net;
    delete netRT;
    return ret;
}
