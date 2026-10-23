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
    mod.addLibraryPath(b.path("./autogen"));
    
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
    mod.linkSystemLibrary("raylib", .{});
    

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
