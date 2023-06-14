project(
    'Pong',
    'cpp',
    version : '0.1.0',
    meson_version : '>= 0.60.0',
    license : 'MIT',
    default_options : [
        'warning_level=3',
        'cpp_std=c++20',
    ]
)

include = include_directories('include')
srcs = files()

subdir('src')

crank_dep = dependency('crank', fallback : ['crank', 'crank'])
rangev3_dep = dependency('range-v3')
fmt_dep = dependency('fmt')
sfml_dep = dependency('sfml')

main = executable(
    'pong',
    srcs,
    include_directories: include,
    dependencies : [
        crank_dep,
        rangev3_dep,
        fmt_dep,
        sfml_dep,
    ]
)
