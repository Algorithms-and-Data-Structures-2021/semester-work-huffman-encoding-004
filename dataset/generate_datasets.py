import json
import random
import os

import text_generator_api_functions

DATASETS_JSON = "datasetsConfig.json"
BENCHMARK_SETTINGS_FILE = "benchmarkSettings.settings"


class Dataset(object):
    def __init__(self, samples_count, output_path):
        self.samples_count = samples_count
        self.output_path = output_path

    def create_dataset(self):
        with open(self.output_path, 'w') as file:
            dataset_body = text_generator_api_functions.get_random_text(self.samples_count)
            file.write(dataset_body)


def create_datasets():
    with open("datasetsConfig.json", "r") as f:
        datasets_dict = json.load(f)

    folder = datasets_dict["folder"]
    file_format = datasets_dict["fileFormat"]

    for dataset_package in datasets_dict["datasetPackages"]:
        target_folder = dataset_package["targetFolder"]
        benchmark_settings_file = open("data/{}/{}".format(target_folder,BENCHMARK_SETTINGS_FILE), "w")

        for dataset in dataset_package["datasets"]:
            Dataset(dataset["samplesCount"],
                    os.path.dirname(__file__) + "/" + folder + target_folder + dataset["outputFileName"] + "." + file_format) \
                .create_dataset()
            benchmark_settings_file.write(dataset["outputFileName"] +
                                          "." + file_format + " " +
                                          str(dataset["samplesCount"]) + " " + str(dataset["numberOfPasses"]) +"\n")
        benchmark_settings_file.close()


if __name__ == "__main__":
    create_datasets()
