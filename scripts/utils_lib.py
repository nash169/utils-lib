#! /usr/bin/env python
# encoding: utf-8

from waflib.Configure import conf
from utils import check_include, check_lib


def options(opt):
    # Options
    opt.add_option(
        "--utilslib-path", type="string", help="path to utilslib-lib", dest="utilslib_path",
    )

    # Required package options
    opt.load("eigen corrade", tooldir="waf_tools")


@conf
def check_utilslib(ctx):
    # Set the search path
    if ctx.options.utilslib_path is None:
        path_check = ["/usr/local", "/usr"]
    else:
        path_check = [ctx.options.utilslib_path]

    # utilslib-lib includes
    check_include(ctx, "UTILSLIB", [""], [
                  "utils_lib/Utils.hpp"], path_check)

    # utilslib-lib libs
    check_lib(ctx, "UTILSLIB", "", ["libUtils"], path_check)

    if ctx.env.LIB_UTILSLIB or ctx.env.STLIB_UTILSLIB:
        # Add dependencies to require libraries
        if "EIGEN" not in ctx.get_env()["libs"]:
            ctx.get_env()["requires"] += ["EIGEN"]
            ctx.load("eigen", tooldir="waf_tools")

        if "CORRADE" not in ctx.get_env()["libs"]:
            ctx.get_env()["requires"] += ["CORRADE"]
            ctx.load("corrade", tooldir="waf_tools")

        # Add library
        ctx.get_env()["libs"] += ["UTILSLIB"]


def configure(cfg):
    if not cfg.env.LIB_UTILSLIB and not cfg.env.STLIB_UTILSLIB:
        cfg.check_utilslib()
