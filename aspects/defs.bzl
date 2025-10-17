def _count_rule_types_impl(target, ctx):
    if hasattr(ctx.rule.attr, 'deps'):
        for dep in ctx.rule.attr.deps:
            print("Dependency: {}".format(dep.label))


    return []

count_rule_types = aspect(
    implementation = _count_rule_types_impl,
    attr_aspects = ["deps"],
)