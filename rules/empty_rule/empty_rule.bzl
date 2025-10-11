def _empty_rule_implementation(ctx):
    pass

empty_rule = rule(
    implementation = _empty_rule_implementation,
    attrs = {},
)