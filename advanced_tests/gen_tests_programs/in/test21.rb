def fun_1(param2)
    param2 = param2 + 2
end

def fun_2(param1)
    c = fun_1(param1)
end

out = fun_2(2)
print out
