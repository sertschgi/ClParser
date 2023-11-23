#include "../include/clparser/Parser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    ClPosArg datasetNamePosArg("dataset-name", true);
    ClOption datasetNameOption(
        "dataset-name", { "n", "name" }, "Specify the name of your dataset.",
        { &datasetNamePosArg }
    );

    ClPosArg datasetLabelPosArg("dataset-label", true);
    ClOption datasetLabelOption(
        "dataset-label", { "l", "labels" },
        "Specify the path of your labelmap.pbtxt", { &datasetLabelPosArg }
    );

    ClPosArg datsetLabelPathPosArg("dataset-label-path", true);
    ClOption datsetLabelPathOption(
        "dataset-label-path", { "a", "labels_path" }, "Specify the label path.", 
        { &datsetLabelPathPosArg }
    );

    ClPosArg datasetImagePathPosArg("dataset-image-path", true);
    ClOption datasetImagePathOption(
        "dataset-image-path", { "m", "images_path" },
        "Specify the images path.", { &datasetImagePathPosArg }
    );
    ClCommand createDatasetCommand(
        "dataset", { &datasetNameOption, &datasetLabelOption,
                     &datsetLabelPathOption, &datasetImagePathOption }, {}
    );

    ClPosArg profileNamePosArg("profile-name", true);
    ClOption profileNameOption(
        "profile-name", { "n", "name" }, "Specify the name of your profile.",
        { &profileNamePosArg }
    );

    ClPosArg profileFrameworkPosArg("profile-framework", true);
    ClOption profileFrameworkOption(
        "profile-framework", { "f", "framework" },
        "Specify the framework you want to use.", { &profileNamePosArg }
    );

    ClPosArg profileScopePosArg("profile-scope", true);
    ClOption profileScopeOption(
        "profile-scope", { "s", "scope" },
        "Specify which field of machine lerning you want to use.", { &profileScopePosArg }
    );

    ClCommand createProfileCommand(
        "profile",
        { &profileNameOption, &profileFrameworkOption, &profileScopeOption }, {}
    );

    ClPosArg projectNamePosArg("project-name", true);
    ClOption projectNameOption(
        "project-name", { "n", "name" }, "Specify the name of your project.",
        { &projectNamePosArg }
    );

    ClPosArg projectProfilePosArg("project-profile", true);
    ClOption projectProfileOption(
        "project-profile", { "p", "profile" },
        "Specify the profile you want to use for your project.", { &projectProfilePosArg }
    );

    ClPosArg projectDatasetPosArg("project-dataset", true);
    ClOption projectDatasetOption(
        "project-dataset", { "d", "dataset" },
        "Specify the dataset you want to use.", { &projectDatasetPosArg }
    );
    ClCommand createProjectCommand(
        "project",
        { &projectNameOption, &projectProfileOption, &projectDatasetOption }, {}
    );

    ClPosArg modelNamePosArg("model-name", true);
    ClOption modelNameOption(
        "model-name", { "n", "name" }, "Specify the name of your model.",
        { &modelNamePosArg }
    );

    ClPosArg modelProjectPosArg("model-project", true);
    ClOption modelProjectOption(
        "model-project", { "p", "project" },
        "Specify the project you want to use for your model.", { &modelProjectPosArg }
    );

    ClPosArg modelModelPosArg("model-model", true);
    ClOption modelModelOption(
        "model-model", { "m", "model" }, "Specify the model you want to use.",
        { &modelModelPosArg }
    );

    ClCommand createModelCommand(
        "model", { &modelNameOption, &modelProjectOption, &modelModelOption }, {}
    );

    ClCommandPtrList createCommands = { &createDatasetCommand,
                                        &createProfileCommand,
                                        &createProjectCommand,
                                        &createModelCommand };

    ClCommand createCommand(std::string("create"), createCommands, {});

    ClParser parser({ &createCommand });
    parser.addAppName("0.0.1");

    parser.parse(argc, argv);

    std::cout << modelModelPosArg.cvalue();
}
