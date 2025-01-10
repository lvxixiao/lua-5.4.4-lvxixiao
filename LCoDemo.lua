local math = require "math"
local co1 = coroutine.create(function(str) 
    -- pcall(print, function() print("xpcall 错误") end, "co1 线程执行")
    print("math.round", math.random())
    coroutine.yield "co1 yield"
    print("co1 恢复执行")
end)

print("主线程执行")
local ret, val = coroutine.resume(co1, "main resume")
print("主线程恢复执行", val)
coroutine.resume(co1)
print("主线程结束")