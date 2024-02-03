#include "clparser/Parser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    // CREATE DATASET

    ClPosArg datasetNamePosArg("dataset-name", true);
    ClOption datasetNameOption(
            "dataset-name", { "n", "name" }, "Specify the name of your dataset.",
            { datasetNamePosArg }
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

    ClCommand createDatasetCommand(
            "dataset", { datasetNameOption, datasetLabelOption,
                         datsetLabelPathOption, datasetImagePathOption }, "creates a dataset"
    );


    // CREATE PROFILE

    ClPosArg profileNamePosArg("profile-name", true);
    ClOption profileNameOption(
            "profile-name", { "n", "name" }, "Specify the name of your profile.",
            { profileNamePosArg }
    );

    ClPosArg profileFrameworkPosArg("profile-framework", true);
    ClOption profileFrameworkOption(
            "profile-framework", { "f", "framework" },
            "Specify the framework you want to use.", { profileNamePosArg }
    );

    ClPosArg profileScopePosArg("profile-scope", true);
    ClOption profileScopeOption(
            "profile-scope", { "s", "scope" },
            "Specify which field of machine learning you want to use.", { profileScopePosArg }
    );

    ClCommand createProfileCommand(
            "profile",
            { profileNameOption, profileFrameworkOption, profileScopeOption },
            "creates a profile"
    );


    // CREATE PROJECT

    ClPosArg projectNamePosArg("project-name", true);
    ClOption projectNameOption(
            "project-name", { "n", "name" }, "Specify the name of your project.",
            { projectNamePosArg }
    );

    ClPosArg projectProfilePosArg("project-profile", true);
    ClOption projectProfileOption(
            "project-profile", { "p", "profile" },
            "Specify the profile you want to use for your project.", { projectProfilePosArg }
    );

    ClPosArg projectDatasetPosArg("project-dataset", true);
    ClOption projectDatasetOption(
            "project-dataset", { "d", "dataset" },
            "Specify the dataset you want to use.", { projectDatasetPosArg }
    );
    ClCommand createProjectCommand(
            "project",
            { projectNameOption, projectProfileOption, projectDatasetOption },
            "creates a project"
    );


    // CREATE MODEL

    ClPosArg modelNamePosArg("model-name", true);
    ClOption modelNameOption(
            "model-name", { "n", "name" }, "Specify the name of your model.",
            { modelNamePosArg }
    );

    ClPosArg modelProjectPosArg("model-project", true);
    ClOption modelProjectOption(
            "model-project", { "p", "project" },
            "Specify the project you want to use for your model.", { modelProjectPosArg }
    );

    ClPosArg modelModelPosArg("model-model", true);
    ClOption modelModelOption(
            "model-model", { "m", "model" }, "Specify the model you want to use.",
            { modelModelPosArg }
    );

    ClCommand createModelCommand(
            "model", { modelNameOption, modelProjectOption, modelModelOption },
            "creates a model"
    );


    // CREATE COMMAND

    ClCommandPtrList createCommands = { createDatasetCommand,
                                        createProfileCommand,
                                        createProjectCommand,
                                        createModelCommand };

    ClCommand createCommand("create", createCommands, "creates your stuff");


    /*    ############################# TRAIN COMMAND #############################    */

    ClPosArg trainProjectPosArg("train-project", true);
    ClOption trainProjectOption(
            "model-project", { "p", "project" },
            "Specify the project your model is located in.", { trainProjectPosArg }
    );

    ClPosArg trainModelPosArg("train-model", true);
    ClOption trainModelOption(
            "train-model", { "m", "model" }, "Specify the model you want to train.",
            { trainModelPosArg }
    );

    ClOptionPtrList trainOptions = { trainProjectOption, trainModelOption };
    ClCommand trainCommand("train", trainOptions, "trains your model");

    /*    ############################# LIST COMMAND #############################    */

    ClOption listDatasetsOption("list-framework", {"d", "datasets"}, "List the datasets.");

    ClOption listProfilesOption("list-profiles", {"r", "profiles"}, "List the profiles.");

    ClOption listProjectsOption("list-projects", {"p", "projects"}, "List the projects.");

    ClPosArg listScopePosArg("list-model-scope");
    ClPosArg listframeworkPosArg("list-model-framework");
    ClOption listModelsOption("list-models", {"s", "model-scope"}, "List the models of a scope (-f required).", { listScopePosArg });

    ClOption listFrameworksOption("list-framework", {"f", "frameworks"}, "List the frameworks.");

    ClOptionPtrList listOptions = {
            listDatasetsOption,
            listProfilesOption,
            listProjectsOption,
            listModelsOption,
            listFrameworksOption
    };
    ClCommand listCommand("list", listOptions, "lists stuff");

    /*    ############################# DELETE COMMAND #############################    */

    ClPosArg deleteDatasetPosArg("delete-dataset");
    ClOption deleteDatasetOption("delete-dataset", {"d", "dataset"}, "Delete a dataset.", { deleteDatasetPosArg });

    ClPosArg deleteProfilePosArg("delete-profile");
    ClOption deleteProfileOption("delete-profile", {"r", "profile"}, "Delete a profile.", { deleteProfilePosArg });

    ClPosArg deleteProjectPosArg("delete-project");
    ClOption deleteProjectOption("delete-project", {"p", "project"}, "Delete a project.", { deleteProjectPosArg });

    ClPosArg deleteModelPosArg("delete-model");
    ClOption deleteModelOption("delete-model", {"m", "model"}, "Delete a model.", { deleteModelPosArg });

    ClOption confirmationOption("confirm", {"y", "yes"}, "Continue without asking.");

    ClOptionPtrList deleteOptions = {
            deleteDatasetOption,
            deleteProfileOption,
            deleteProjectOption,
            deleteModelOption,
            confirmationOption
    };

    ClCommand deleteCommand("delete", deleteOptions, "deletes stuff");


    /*    ############################# PARSER #############################    */

    ClParser parser({ createCommand, listCommand, trainCommand, deleteCommand });
    parser.addAppName("0.0.1");
    parser.addHelpOption();

    parser.parse(argc, argv);

    if (datasetNamePosArg.isSet())
        cout << "set" << endl << datasetNamePosArg.cvalue() << endl;
        cout << datasetLabelPosArg.cvalue() << endl;

    cout << "finished";
}