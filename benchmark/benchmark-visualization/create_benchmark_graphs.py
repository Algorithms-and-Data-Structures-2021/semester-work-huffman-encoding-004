import matplotlib.pyplot as plt
import os
import json

BENCHMARK_RESULTS_PATH = "./benchmark-results"
BENCHMARK_GRAPHS_PATH = "./benchmark-graphs"
BENCHMARK_GRAPHS_JSON_PATH = "benchmarkGraphs.json"


class BenchmarkResult(object):
    def __init__(self, name: str):
        self.samples_count_list = []
        self.time_list = []
        self.name = name

    def add_result(self, samples_count:int, time:float):
        self.samples_count_list.append(samples_count)
        self.time_list.append(time)

    def replace_with_average_values(self):
        d = {}
        for i in range(len(self.samples_count_list)):
            d[self.samples_count_list[i]] = self.time_list[i]

        self.samples_count_list = []
        self.time_list = []

        for key, value in d.items():
            self.samples_count_list.append(key)
            self.time_list.append(value)


    def __repr__(self):
        return "BenchmarkResult(name=%s)" % self.name


def get_benchmark_results() -> dict:
    benchmark_csv_results = []
    # csv benchmark results open
    for root, dirs, files in os.walk(BENCHMARK_RESULTS_PATH):
        for file in files:
            benchmark_csv_results.append(open(BENCHMARK_RESULTS_PATH + "/" + file, "r"))

    benchmark_results = {}

    for benchmark_csv_result in benchmark_csv_results:
        benchmark_result = BenchmarkResult(benchmark_csv_result.name)

        benchmark_csv_result.readline()
        for line in benchmark_csv_result:
            samples_count = int(line.split(",")[0])
            time = float(line.split(",")[1])
            benchmark_result.add_result(samples_count, time)

        benchmark_result.replace_with_average_values()
        benchmark_results[benchmark_result.name] = benchmark_result

    # closing files
    for benchmark_result in benchmark_csv_results:

        benchmark_result.close()

    return benchmark_results


def create_graphs():
    benchmark_results = get_benchmark_results()

    with open(BENCHMARK_GRAPHS_JSON_PATH, "r") as f:
        benchmark_graphs_json = json.load(f)

    benchmark_graphs = benchmark_graphs_json["benchmarkGraphs"]

    for benchmark_graph in benchmark_graphs:
        fig, ax = plt.subplots()
        fig.set_size_inches(10,5)
        for source in benchmark_graph["sources"]:
            ax.plot(benchmark_results[BENCHMARK_RESULTS_PATH + "/" + source].samples_count_list,
                    benchmark_results[BENCHMARK_RESULTS_PATH + "/" + source].time_list,
                    label=source)
        ax.set_xlabel('кол-во данных')
        ax.set_ylabel('время, нс')
        ax.set_title(benchmark_graph["title"])
        ax.legend()
        plt.savefig(BENCHMARK_GRAPHS_PATH + "/" + benchmark_graph["outputFile"])
        plt.clf()


if __name__ == "__main__":
    create_graphs()
