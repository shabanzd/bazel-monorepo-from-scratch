def _expand_template_impl(ctx):
    out = ctx.actions.declare_file(ctx.attr.output)
    ctx.actions.expand_template(
        output = out,
        template = ctx.file.template,
        substitutions = ctx.attr.substitutions,
    )

    return DefaultInfo(files = depset([out]))



expand_template = rule(
    implementation = _expand_template_impl,
    attrs = {
        "template": attr.label(allow_single_file = True, mandatory = True),
        "output": attr.string(mandatory = True),
        "substitutions": attr.string_dict(mandatory = True),
    }
)