#include "clparser/Parser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    ClPosArg datasetNamePosArg("dataset-name", true);
    ClPosArgPtrList posarglist = { datasetNamePosArg };

    ClOption datasetNameOption(
        "dataset-name", { "n", "name" }, "Specify the name of your dataset.",
        posarglist
    );

    ClPosArg datasetLabelPosArg("dataset-label", true);
    ClOption datasetLabelOption(
        "dataset-label", { "l", "labels" },
        "Specify the path of your labelmap.pbtxt", { datasetLabelPosArg }
    );

    ClPosArg datsetLabelPathPosArg("dataset-label-path", true);
    ClOption datsetLabelPathOption(
        "dataset-label-path", { "a", "labels_path" }, "Specify the label path.", 
        { datsetLabelPathPosArg }
    );

    ClPosArg datasetImagePathPosArg("dataset-image-path", true);
    ClOption datasetImagePathOption(
        "dataset-image-path", { "m", "images_path" },
        "Specify the images path.", { datasetImagePathPosArg }
    );

    ClOptionPtrList optlist = { datasetNameOption, datasetLabelOption };

    ClCommand createDatasetCommand(
        "dataset", optlist, "creates a Dataset"
    );

    ClCommandPtrList cmdlist = { createDatasetCommand };
    ClCommand createCommand("create", cmdlist, "creates stuff");

    ClCommandPtrList bcmdlist = { createCommand };

    ClParser parser(bcmdlist);
    parser.addAppName("test1");
    parser.addAppVersion("0.1-test");
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addForAllLayers(ClOption({"test"},{"test"},{"test"}));


    parser.parse(argc, argv);

    if (datasetNamePosArg.isSet())
        cout << "set" << endl << datasetNamePosArg.cvalue() << endl;
        cout << datasetLabelPosArg.cvalue() << endl;

    cout << "finished";
}