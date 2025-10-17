load("//rules/expand_template:expand_template.bzl", "expand_template")
expand_template(
    name = "personal_info",
    template = ":personal_info.json.tpl",
    output = "personal_info.json",
    substitutions = {
        "{{name}}": "John Doe",
        "{{age}}": "30",
    }
) 
