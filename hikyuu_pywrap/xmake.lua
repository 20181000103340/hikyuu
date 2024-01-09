
add_requires("pybind11", {system = false, alias = "pybind11"})

target("core")
    set_kind("shared")
    if is_mode("debug") then 
        set_default(false) --会默认禁用这个target的编译，除非显示指定xmake build _hikyuu才会去编译，但是target还存在，里面的files会保留到vcproj
        --set_enable(false) --set_enable(false)会彻底禁用这个target，连target的meta也不会被加载，vcproj不会保留它
    end

    add_options("stackstrace")

    add_deps("hikyuu")
    add_packages("boost", "fmt", "spdlog", "flatbuffers", "pybind11", "cpp-httplib")
    if is_plat("windows") then
        set_filename("core.pyd")
        add_cxflags("-wd4251")
    else 
        set_filename("core.so")
    end

    if is_plat("windows") and is_mode("release") then
        add_defines("HKU_API=__declspec(dllimport)")
        add_cxflags("-wd4566")
    end
    
    local cc = get_config("cc")
    local cxx = get_config("cxx")
    if (cc and string.find(cc, "clang")) or (cxx and string.find(cxx, "clang")) then
        add_cxflags("-Wno-error=parentheses-equality -Wno-error=missing-braces")
    end

    add_includedirs("../hikyuu_cpp")
    add_files("./**.cpp")

    add_rpathdirs("$ORIGIN", "$ORIGIN/lib", "$ORIGIN/../lib")

    on_load("windows", "linux", "macosx", function(target)
        import("lib.detect.find_tool")
        if is_plat("windows") then
            -- detect installed python3
            local python = assert(find_tool("python", {version = true}), "python not found, please install it first! note: python version must > 3.0")
            assert(python.version > "3", python.version .. " python version must > 3.0, please use python3.0 or later!")
            -- find python include and libs directory
            local pydir = os.iorun("python -c \"import sys; print(sys.executable)\"")
            pydir = path.directory(pydir)
            target:add("includedirs", pydir .. "/include")
            target:add("linkdirs", pydir .. "/libs")
            return
        end
    
        -- get python include directory.
        local pydir = try { function () return os.iorun("python3-config --includes"):trim() end }
        assert(pydir, "python3-config not found!")
        target:add("cxflags", pydir)   
    end)

    after_build(function(target)
        if is_plat("macosx") then
            os.run(format("install_name_tool -change @rpath/libhikyuu.dylib @loader_path/libhikyuu.dylib %s/%s", target:targetdir(), "core.so"))
        end

        local dst_dir = "$(projectdir)/hikyuu/cpp/"
        if is_plat("windows") then
            os.cp(target:targetdir() .. '/core.pyd', dst_dir)
            os.cp(target:targetdir() .. '/*.dll', dst_dir)
        elseif is_plat("macosx") then
            os.cp(target:targetdir() .. '/core.so', dst_dir)
            os.cp(target:targetdir() .. '/libhikyuu.dylib', dst_dir)
        else
            os.trycp(target:targetdir() .. '/*.so', dst_dir)
            os.trycp(target:targetdir() .. '/*.so.*', dst_dir)
        end
    end)


