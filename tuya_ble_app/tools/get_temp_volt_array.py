# 导入xlrd模块
import xlrd

# 读取电阻值
def read_resistance_value(file_name, sheet_name, start_col, total_col, start_row, temp_min, temp_max):
    resistance_value = []
    read_col = start_col
    workbook = xlrd.open_workbook(file_name)
    table = workbook.sheet_by_name(sheet_name)
    nrows = table.nrows
    for col in range(total_col):
        for row in range(start_row, nrows):
            temp = table.cell_value(row, read_col)
            if temp <= temp_max:
                if temp >= temp_min:
                    resistance_value.append(table.cell_value(row, read_col+1))
            else:
                break; 
        read_col += 2
    return resistance_value

# 计算电压值(mV)
def calculate_resistance_value_to_mvol_value(ntc_res_k_list, div_res_k, vcc, up_down):
    mvol_value_list = []
    for ntc_res_k in ntc_res_k_list:
        if up_down == 1:
            voltage = vcc * (div_res_k / (ntc_res_k + div_res_k))
        else:
            voltage = vcc * (ntc_res_k / (ntc_res_k + div_res_k))
        mvol_value_list.append(int(voltage*1000))
    return mvol_value_list

# 转换为可直接复制的数组信息
def transform_mvol_value_to_array(mvol_value, temp_min, temp_max, digit):
    mvol_value_s = "    "
    num = temp_min
    total = temp_max - temp_min + 1
    count_to_know_end = 0
    count_to_change_line = 0

    for data in mvol_value:
        if data < 10**(digit-1):
            mvol_value_s = mvol_value_s + " " + str(data)
        else:
            mvol_value_s = mvol_value_s + str(data)
        count_to_know_end += 1
        count_to_change_line += 1
        if count_to_change_line >= 20:
            count_to_change_line = 0
            if count_to_know_end < total:
                mvol_value_s = mvol_value_s + ", /* " + str(num) + " ~ " + str(num+20-1) + " */\n    "
                num += 20
            else:
                mvol_value_s = mvol_value_s + "  /* " + str(num) + " ~ " + str(num+20-1) + " */"
        else:
            if count_to_know_end < total:
                mvol_value_s = mvol_value_s + ", "
            else:
                mvol_value_s = mvol_value_s + "  /* " + str(num) + " ~ " + str(temp_max) + " */"
    print(mvol_value_s)
    return

temp_resistance_value = read_resistance_value("R-T.xlsx", "Sheet1", 0, 4, 2, 0, 119)
temp_adc_value = calculate_resistance_value_to_mvol_value(temp_resistance_value, 20, 3.3, 1)
transform_mvol_value_to_array(temp_adc_value, 0, 119, 4)
