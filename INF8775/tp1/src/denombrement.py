def denombrement(the_list):
    result = [0] * (max(the_list) + 1)
    for x in range(0, len(the_list)):
        result[the_list[x]] = result[the_list[x]] + 1

    index = 0

    for value, count in enumerate(result):
        if count != 0:
            for _ in range(count):
                the_list[index] = value
                index += 1
