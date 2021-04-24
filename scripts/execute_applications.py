import os
from subprocess import Popen, PIPE


def generate_args(binary, *params):
    arguments = [binary]
    arguments.extend(list(params))
    return arguments


def execute_binary(args):
    process = Popen(' '.join(args), shell=True, stdout=PIPE, stderr=PIPE)
    # process = Popen(' '.join(args), shell=True, stdout=sys.stdout, stderr=sys.stderr)
    (std_output, std_error) = process.communicate()
    process.wait()
    rc = process.returncode
    return rc, std_output.decode("utf-8"), std_error.decode("utf-8")


def execute(binary_path, graph_path, execution_mode, sampling_method, source_type,
            walk_num, length, thread_num, result_file):
    # Execute the binary.
    execution_args = generate_args(binary_path, '-f', graph_path, '-em', str(execution_mode),
                                   '-sm', str(sampling_method), '-st', str(source_type),
                                   '-wn', str(walk_num), '-l', str(length), '-n', str(thread_num), '-ew')
    print('Cmd: {0}'.format(' '.join(execution_args)))

    (rc, std_output, std_error) = execute_binary(execution_args)
    if rc == 0:
        print('Execute successfully.')
    else:
        print('Execute error. {0} {1}'.format(std_output, std_error))

    result = '{0}\n{1}\n{2}'.format(' '.join(execution_args), std_output, std_error)

    with open(result_file, 'w') as f:
        f.write(result)


# result file format:
# binary: creeper, creeperN, homegrown
# application: genericwalk, deepwalk, ppr, node2vec, metapath
# execution mode: uniform, static, dynamic
# sampling method: uniform, its, alias, rejection, maxweightrejection
# source type: all, single, multiple
# (binary)_(application)_(execution mode)_(sampling method)_(source type)_(num walks)_(length)_(thread).res

application_names = ['genericwalk', 'deepwalk', 'ppr', 'node2vec', 'metapath']
execution_mode_name = ['uniform', 'static', 'dynamic']
sampling_method_name = ['uniform', 'its', 'alias', 'rejection', 'maxweightrejection']
source_type_name = ['all', 'single', 'multiple']


# Execute creeperN
# binary_name = 'creeperN'
# build_type = 'cn_build'

# Execute creeper
binary_name = 'creeper'
build_type = 'creeper_build'


project_path = '/home/yuhang/Work'
dataset_path = '/data/graph_at_scale/dataset'
result_path = '/data/graph_at_scale/creeper_results/logs'

input_binary_path_format = project_path + '/XtraGraphComputing/{0}/random_walk/{1}.out'
input_graph_path_format = dataset_path + '/{0}'
input_result_path_format = result_path + '/{0}/{1}'

input_application_list = [
   # 0, # genericwalk
    1, # deepwalk
    2, # ppr
    3, # node2vec
    4, # metapath
]

input_execution_mode_list = [
    0, # uniform
    1, # static
    2, # dynamic
]

uniform_valid_sampling_list = [0]
static_valid_sampling_list = [1, 2, 3]
dynamic_valid_sampling_list = [1, 2, 3, 4]

valid_sampling_list = [uniform_valid_sampling_list, static_valid_sampling_list, dynamic_valid_sampling_list]

input_sampling_method_list = [
    0, # uniform
    1, # its,
    2, # alias
    3, # rejection
    4, # maxweightrejection
]

input_source_type_list = [
    0, # all
    1, # single
    2, # multiple
]

input_length_list = [
    # 5,
    # 6,
    80
    # 160
]

input_walk_num_list = [
    0
]

input_graph_list = [
    # 'eu2005',
    # 'orkut',
    # 'patents',
    # 'uk2002',
    # 'youtube',
    # 'livejournal',
    # 'twitter',
    # 'friendster',
    # 'amazon_book',
    # 'amazon_clothing',
    'wikidata',
    'amazon',
]

input_thread_num_list = [
    10
]

# [execution mode, sampling method, source type, extend command]
input_application_configuration_dict_list = [
    {1: [1, 2, 0, ''], 2: [0, 0, 1, ''], 3: [2, 4, 0, ''], 4: [2, 1, 0, '-s 0,1,2,3,4 -el']},
    # {0: [0, 0, 0, '']},
    # {0: [1, 1, 0, '']},
    # {0: [1, 2, 0, '']},
    # {0: [1, 3, 0, '']},
    # {0: [2, 4, 0, '']},
]

# (binary)_(application)_(execution mode)_(sampling method)_(source type)_(source_num)_(length)_(thread).res

for input_graph in input_graph_list:
    for input_application_configuration_dict in input_application_configuration_dict_list:
        for input_application in input_application_list:
            input_execution = input_application_configuration_dict[input_application][0]
            input_sampling = input_application_configuration_dict[input_application][1]
            input_source_type = input_application_configuration_dict[input_application][2]
            input_cmd_extension = input_application_configuration_dict[input_application][3]

            for input_walk_num in input_walk_num_list:
                for input_length in input_length_list:
                    for input_thread_num in input_thread_num_list:
                        if input_application == 2:
                            input_length = 5
                        elif input_application == 4:
                            input_length = 6
                        result_file_name = '{0}_{1}_{2}_{3}_{4}_{5}_{6}_{7}.res'.format(binary_name,
                                                                                        application_names[input_application],
                                                                                        execution_mode_name[input_execution],
                                                                                        sampling_method_name[input_sampling],
                                                                                        source_type_name[input_source_type],
                                                                                        input_walk_num,
                                                                                        input_length,
                                                                                        input_thread_num)

                        input_binary_path = input_binary_path_format.format(build_type,
                                                                            application_names[input_application])
                        input_graph_path = input_graph_path_format.format(input_graph)
                        input_result_path = input_result_path_format.format(input_graph, result_file_name)

                        print(input_graph_path)
                        print(input_result_path)
                        print(input_binary_path)

                        if os.path.exists(input_result_path):
                            print('Result exists.')
                            # continue

                        if not os.path.exists(os.path.dirname(input_result_path)):
                            os.makedirs(os.path.dirname(input_result_path))

                        input_binary_path = ' '.join([input_binary_path, input_cmd_extension])
                        execute(input_binary_path, input_graph_path, input_execution, input_sampling,
                                input_source_type, input_walk_num, input_length, input_thread_num,
                                input_result_path)
                        print('-------------------------------------------------------------------------------')
