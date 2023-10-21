#include "../include/clparser/Parser.hpp"

int main(int argc, char* argv[]) {
    ClPosArg datasetNamePosArg("dataset-name");
    ClOption datasetNameOption(
        "dataset-name", { "n", "name" }, "Specify the name of your dataset.",
        { &datasetNamePosArg }, true
    );

    ClOption datasetLabelOption(
        "dataset-label", { "l", "labels" },
        "Specify the path of your labelmap.pbtxt", true
    );
    ClOption datsetLabelPathOption(
        "dataset-label-path", { "a", "labels_path" }, "Specify the label path.",
        true
    );
    ClOption datasetImagePathOption(
        "dataset-image-path", { "m", "images_path" },
        "Specify the images path.", true
    );
    ClCommand createDatasetCommand(
        "dataset", { &datasetNameOption, &datasetLabelOption,
                     &datsetLabelPathOption, &datasetImagePathOption }
    );

    ClOption profileNameOption(
        "profile-name", { "n", "name" }, "Specify the name of your profile.",
        true
    );
    ClOption profileFrameworkOption(
        "profile-framework", { "f", "framework" },
        "Specify the framework you want to use.", true
    );
    ClOption profileScopeOption(
        "profile-scope", { "s", "scope" },
        "Specify which field of machine lerning you want to use.", true
    );
    ClCommand createProfileCommand(
        "profile",
        { &profileNameOption, &profileFrameworkOption, &profileScopeOption }
    );

    ClOption projectNameOption(
        "project-name", { "n", "name" }, "Specify the name of your project.",
        true
    );
    ClOption projectProfileOption(
        "project-profile", { "p", "profile" },
        "Specify the profile you want to use for your project.", true
    );
    ClOption projectDatasetOption(
        "project-dataset", { "d", "dataset" },
        "Specify the dataset you want to use.", true
    );
    ClCommand createProjectCommand(
        "project",
        { &projectNameOption, &projectProfileOption, &projectDatasetOption }
    );

    ClOption modelNameOption(
        "model-name", { "n", "name" }, "Specify the name of your model.", true
    );
    ClOption modelProjectOption(
        "model-project", { "p", "project" },
        "Specify the project you want to use for your model.", true
    );
    ClOption modelModelOption(
        "model-model", { "m", "model" }, "Specify the model you want to use.",
        true
    );
    ClCommand createModelCommand(
        "model", { &modelNameOption, &modelProjectOption, &modelModelOption }
    );

    ClCommandPtrList createCommands = { &createDatasetCommand,
                                        &createProfileCommand,
                                        &createProjectCommand,
                                        &createModelCommand };

    ClCommand createCommand(std::string("create"), createCommands);

    ClParser parser({ &createCommand });
    parser.addAppName("0.0.1");

    parser.parse(argc, argv);
}
