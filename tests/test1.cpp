#include "../include/clparser/Parser.hpp"

int main(int argc, char* argv[])
{
    ClOption * datasetNameOption = new ClOption("dataset-name", {"n", "name"}, "Specify the name of your dataset.", true);
    ClOption * datasetLabelOption = new ClOption("dataset-label", {"l", "labels"}, "Specify the path of your labelmap.pbtxt", true);
    ClOption * datsetLabelPathOption = new ClOption("dataset-label-path", {"a", "labels_path"}, "Specify the label path.", true);
    ClOption * datasetImagePathOption = new ClOption("dataset-image-path", {"m", "images_path"}, "Specify the images path.", true);
    ClCommand * createDatasetCommand = new ClCommand(
        "dataset",
        {
         datasetNameOption,
         datasetLabelOption,
         datsetLabelPathOption,
         datasetImagePathOption
        }
    );
    /*
    ClOption profileNameOption({"n", "name"}, "Specify the name of your profile.", true);
    ClOption profileFrameworkOption({"f", "framework"}, "Specify the framework you want to use.", true);
    ClOption profileScopeOption({"s", "scope"}, "Specify which field of machine lerning you want to use.", true);
    ClCommand createProfileCommand(
        "profile",
        {
         profileNameOption,
         profileFrameworkOption,
         profileScopeOption
        }
    );


    ClCommand createProjectCommand("project", projectOptions);
    ClCommand createModelCommand("model", modelOptions);
    */
    ClCommandPtrList createCommands = {
        createDatasetCommand
    };

    ClCommand * createCommand = new ClCommand(std::string("create"), createCommands);

    ClParser parser({createCommand});
    parser.addHelpOption();
    parser.addAppName("test");

    cout << "before parsing";

    parser.parse(argc, argv);
}
