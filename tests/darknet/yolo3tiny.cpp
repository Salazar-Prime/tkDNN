#include<iostream>
#include<vector>
#include "tkdnn.h"
#include "test.h"
#include "DarknetParser.h"

int main() {
    std::string bin_path  = "yolo3tiny";
    std::vector<std::string> input_bins = { 
        bin_path + "/layers/input.bin"
    };
    std::vector<std::string> output_bins = {
        bin_path + "debug/layer23_out.bin",
    };
    std::string wgs_path  = bin_path + "/layers";
    std::string cfg_path  = "../tests/darknet/cfg/yolo3tiny.cfg";
    std::string name_path = "../tests/darknet/names/coco.names";
    downloadWeightsifDoNotExist(input_bins[0], bin_path, "https://cloud.hipert.unimore.it/s/LMcSHtWaLeps8yN/download");

    // parse darknet network
    tk::dnn::Network *net = tk::dnn::darknetParser(cfg_path, wgs_path, name_path);
    net->print();

    //convert network to tensorRT
    tk::dnn::NetworkRT *netRT = new tk::dnn::NetworkRT(net, net->getNetworkRTName(bin_path.c_str()));
    
    int ret = testInference(input_bins, output_bins, net, netRT);
    delete net;
    delete netRT;
    return ret;
}