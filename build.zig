const std = @import("std");
const builtin = @import("builtin");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const mod = b.addModule("c_opengl_boilerplate", .{
        .target = target,
        .optimize = optimize,
        .link_libc = true
    });
    mod.addIncludePath(b.path("./vendor/raylib/src"));
    mod.addIncludePath(b.path("./utils/"));

    const c_source_files = [_][]const u8{
        "main.c",
    };

    const c_flags = [_][]const u8{
        "-O0",
        "-g",
        "-Wall",
        "-Wextra",
        "-Werror"
    };

    mod.addCSourceFiles(.{
        .files = &c_source_files,
        .flags = &c_flags
    });
    
    //TODO: build raylib (static) with zig, then output it to autogen/
    //const default_raylib_build_options = [_][]const u8{
        //"cd",
        //"vendor/raylib/src",
        //"&&",
        //"make",
        //"PLATFORM=PLATFORM_DESKTOP_RGFW",
        //"&&",
        //"cd",
        //"../../../"
    //};
//
    //var not_exist: bool = false;
    //var raylib_dir: std.Io.Dir = undefined;
    //var raylib_lib: std.Io.File = undefined;
//
    //var check_autogen = std.Io.Dir.openDir(std.Io.Dir.cwd(), std.Io.failing, "autogen", .{});
    //if(check_autogen) |value| {
        //raylib_dir = value;
    //} else |err| {
        //if(err == error.FileNotFound){
            //const permissions = std.Io.File.Permissions.default_dir;
            //std.Io.Dir.createDir(std.Io.Dir.cwd(), std.Io.failing, "autogen", permissions)
                //catch |create_err| switch(create_err){
                    //else => std.debug.print("Cannot create autogen!\n", .{})
                //};
            //check_autogen = std.Io.Dir.openDir(std.Io.Dir.cwd(), std.Io.failing, "autogen", .{});
        //}
    //}
//
    //not_exist = false;
//
    //var check_raylib = std.Io.Dir.openFile(raylib_dir, std.Io.failing, "libraylib.a", .{});
    //if(check_raylib) |value| {
        //raylib_lib = value;
    //} else |err| {
        //if(err == error.FileNotFound){
        //_ = b.addSystemCommand(&default_raylib_build_options);
            //if(std.Io.Dir.rename(std.Io.Dir.cwd(), "vendor\\raylib\\src\\libraylib.a", std.Io.Dir.cwd(), "autogen\\libraylib.a", std.Io.failing)){} else |_| {}
            //check_raylib = std.Io.Dir.openFile(raylib_dir, std.Io.failing, "libraylib.a", .{});
        //}
    //}

    //std.Io.File.close(raylib_lib, std.Io.failing);
    //std.Io.Dir.close(raylib_dir, std.Io.failing);

    //In case you have a pre-compiled raylib.
    mod.addLibraryPath(b.path("./autogen"));
    mod.linkSystemLibrary("raylib", .{});
    
    mod.linkSystemLibrary("m", .{});
    switch(builtin.target.os.tag){
        .windows => {
            mod.linkSystemLibrary("opengl32", .{});
            mod.linkSystemLibrary("gdi32", .{});
        },
        .macos => {
            mod.linkFramework("CoreVideo", .{});
            mod.linkFramework("Cocoa", .{});
            mod.linkFramework("OpenGL", .{});
            mod.linkFramework("IOKit", .{});
        },
        .linux => {
            mod.linkSystemLibrary("X11", .{});
            mod.linkSystemLibrary("Xrandr", .{});
            mod.linkSystemLibrary("GL", .{});
            mod.linkSystemLibrary("GLX", .{});
        },
        else => {}
    }
    

    const exe = b.addExecutable(.{
        .name = "run",
        .root_module = mod
    });

    b.installArtifact(exe);

    const run_step = b.step("run", "Run the app");
    const run_cmd = b.addRunArtifact(exe);
    run_step.dependOn(&run_cmd.step);
    run_cmd.step.dependOn(b.getInstallStep());
    run_cmd.addPassthruArgs();
}
