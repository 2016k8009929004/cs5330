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


def execute(binary_path, result_file, first_para, second_para):
    # Execute the binary.
    execution_args = generate_args(binary_path, first_para, second_para)
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
# application: collision_check, linear_probing, cuckoo_hashing
# (application)_(first parameters)_(second parameters).res

application_names = ['collision_check', 'linear_probing', 'cuckoo_hashing']


project_path = '/home/yuhang/Work/cs5330'

input_binary_path_format = project_path + '/build/{0}/{0}_{1}.out'
input_result_path_format = project_path + '/results/{0}'

input_application_list = [
    # 0,  # collision_check
    # 1,  # linear_probing
    2,  # cuckoo_hashing
]

hash_function_list = [
    "simple",
    "twisted",
    "double"
]

first_parameter_list = [
    [10**5, 10**6, 10**7, 10**8],
    [10**5, 10**6, 10**7, 10**8],
    [10**5, 10**6, 10**7, 10**8],
]

second_parameter_list = [
    [0, 0, 0, 0],  #
    [10**4, 10**5, 10**6, 10**7],
    # [0.01, 0.01, 0.01, 0.01, 0.01],
    [0.001, 0.001, 0.001, 0.001, 0.001],
]

for i in input_application_list:
    application = application_names[i]
    for hash_function in hash_function_list:
        for j in range(len(first_parameter_list[i])):
            first_para = first_parameter_list[i][j]
            second_para = second_parameter_list[i][j]
            input_binary_path = input_binary_path_format.format(application, hash_function)
            input_result_path = input_result_path_format.format(application)
            result_file_name = input_result_path + '/{0}_{1}_{2}_{3}.res'.format(application, hash_function, first_para, second_para)

            if not os.path.exists(os.path.dirname(input_result_path)):
                os.makedirs(os.path.dirname(input_result_path))

            print(' '.join((input_binary_path, str(first_para), str(second_para))))

            execute(input_binary_path, result_file_name, str(first_para), str(second_para))

            print('-------------------------------------------------------------------------------')
