

desktop_path = "/Users/ericcacciavillani/Desktop"
project_name = "/Comparing\ C++\ and\ Assembly\ Calculators/Test\ Case\ Results"

full_path_to_C_results = desktop_path + project_name + "\ASM_Test_Results.txt"
full_path_to_ASM_results = desktop_path + project_name + "\C++_Test_Results.txt"


with open(full_path_to_C_results) as f:
    content = f.readlines()
    print(content)



