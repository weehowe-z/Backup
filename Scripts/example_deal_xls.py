#!/usr/bin/env python

import xlrd
import json
import requests


META_TABLE_ID = [0, 1, 2, 3, 4]
DATA_TABLE_ID = [7, 8, 9, 10, 11]

SHEET_NAME = 'accordercore/acc_rule.xlsx'

# URL_BASE = 'http://127.0.0.1:7777'
URL_BASE = 'http://payboss-d0073.alipay.net'

RULE_INIT_URL = URL_BASE + '/ardd/rule/initRule.json'
RULE_CLAUSE_INIT_URL = URL_BASE + '/ardd/rule/initRuleClause.json'

# STYLE IS 'trival' or 'makeRule'
SCRIPT_STYLE = 'trival'
# False will only print to console
POST_TO_DB = False


def postRuleInfo(url, ruleInfo):
    r = requests.post(url, data={'ruleInfo': ruleInfo})
    print(r.json())


def getMetaData(workbook, col):
    table = workbook.sheets()[col]

    metaData = {}

    metaData['RULE_CODE'] = table.cell(0, 1).value
    metaData['RULE_NAME'] = table.cell(1, 1).value
    metaData['RULE_CONDITION_DIMENSIONS'] = table.row_values(2)[1:]
    metaData['RULE_RESULT_DIMENSIONS'] = table.row_values(3)[1:]

    return metaData


def generateRuleClauseList(workbook, col, metaData):
    table = workbook.sheets()[col]

    rule_clauses = []

    rule_dimensions = table.row_values(0)

    rule_condition_dimensions = metaData['RULE_CONDITION_DIMENSIONS']

    rule_clause = {}

    if (SCRIPT_STYLE == 'makeRule'):
        combine_script = "mutex( "
    elif (SCRIPT_STYLE == 'trival'):
        combine_script = "def map;def rules = new Closure[" + str(
            table.nrows - 1) + "];"

    for row in range(1, table.nrows):

        rule_script = generateScript(row, table.row_values(
            row), rule_dimensions, rule_condition_dimensions)
        rule_clause["name"] = metaData['RULE_CODE']
        rule_clause["subName"] = rule_clause["name"] + "_" + str(row)
        rule_clause["description"] = "description_" + str(row)
        rule_clause["type"] = "general"
        rule_clause["status"] = "released"
        rule_clause["scriptReleased"] = rule_script
        rule_clause["scriptEditing"] = rule_script
        if (SCRIPT_STYLE == 'makeRule'):
            combine_script += "subRule" + str(row)
            if (row != table.nrows - 1):
                combine_script += ","
        elif (SCRIPT_STYLE == 'trival'):
            combine_script += "rules[" + \
                str(row - 1) + "] = subRule" + str(row)
            combine_script += "; "

        rule_clauses.append(json.dumps(rule_clause))

        if (POST_TO_DB):
            postRuleInfo(RULE_CLAUSE_INIT_URL, json.dumps(rule_clause))
        else:
            print(rule_clause)
            # print(json.dumps(rule_clause))
            print("-------")

    if (SCRIPT_STYLE == 'trival'):
        combine_script += "for (int i=0; i<" + str(table.nrows -1) + "; ++i){map = rules[i].call(); if ((map != null) return map;)"

    rule_clause["subName"] = 'mutexRule'
    rule_clause["description"] = 'mutexRule'
    rule_clause["type"] = 'mutex'
    rule_clause["scriptReleased"] = combine_script + ")"
    rule_clause["scriptEditing"] = combine_script + ")"

    if (POST_TO_DB):
        postRuleInfo(RULE_CLAUSE_INIT_URL, json.dumps(rule_clause))
    else:
        print(rule_clause)
        print("-------")

    rule_clauses.append(rule_clause)
    return rule_clauses


def generateScript(row, row_values, rule_dimensions, rule_condition_dimensions):
    if (SCRIPT_STYLE == 'makeRule'):
        script = "def subRule" + str(row) + " = makeRule( \"description\", "
        conditionScript = ""
        resultScript = "def map= ["

        for i in range(0, len(row_values)):
            # if (row_values[i] != None and row_values[i] != ''):
            if (row_values[i] != None):
                # To fix default read as float
                # if (rule_dimensions[i] == "subBizType"):
                if (rule_dimensions[i] == "subBizType" and row_values[i] != ''):
                    row_values[i] = int(row_values[i])

                if (rule_dimensions[i] in rule_condition_dimensions):
                    if (row_values[i] == ""):
                        conditionScript += "(!ruleMap.get(\"" + rule_dimensions[
                            i] + "\")) && "
                    else:
                        conditionScript += "(ruleMap.get(\"" + rule_dimensions[
                            i] + "\") == \"" + str(row_values[i]) + "\") && "
                else:
                    resultScript += "\"" + \
                        rule_dimensions[i] + "\":\"" + \
                        str(row_values[i]) + "\","
        conditionScript = conditionScript[:-4]
        script += "{" + conditionScript + "}, {" + \
            resultScript[:-1] + "]; return map;})"

        return script

    elif (SCRIPT_STYLE == 'trival'):

        script = "def subRule" + str(row) + " = { if"
        conditionScript = ""
        resultScript = "def resultMap= ["

        for i in range(0, len(row_values)):
            # if (row_values[i] != None and row_values[i] != ''):
            if (row_values[i] != None):
                # To fix default read as float
                # if (rule_dimensions[i] == "subBizType"):
                if (rule_dimensions[i] == "subBizType" and row_values[i] != ''):
                    row_values[i] = int(row_values[i])

                if (rule_dimensions[i] in rule_condition_dimensions):
                    if (row_values[i] == ""):
                        conditionScript += "(!ruleMap.get(\"" + rule_dimensions[
                            i] + "\")) && "
                    else:
                        conditionScript += "(ruleMap.get(\"" + rule_dimensions[
                            i] + "\") == \"" + str(row_values[i]) + "\") && "
                else:
                    resultScript += "\"" + \
                        rule_dimensions[i] + "\":\"" + \
                        str(row_values[i]) + "\","
        conditionScript = conditionScript[:-4]
        script += "(" + conditionScript + ") {" + \
            resultScript[:-1] + "]; return resultMap;})"

        return script


def generateRule(metaData):
    rule = {}

    rule['name'] = metaData['RULE_CODE']
    rule['description'] = metaData['RULE_NAME']
    rule['type'] = 'biz'
    rule['namespace'] = 'accordercore'
    rule['business'] = 'default'
    rule['status'] = 'released'
    rule['scriptLanguage'] = 'groovy'
    rule['scriptType'] = 'rule'
    rule['extInfo'] = 'autogenByScript'

    if (POST_TO_DB):
        postRuleInfo(RULE_INIT_URL, json.dumps(rule))
    else:
        print(rule)

    return rule


def exportToFile(name, data):
    file = open(metaData['RULE_CODE'] + '.txt', 'wb+')
    file.write(data.encode('utf-8'))
    file.close()

if __name__ == '__main__':
    workbook = xlrd.open_workbook(SHEET_NAME)
    # test()

    for i in range(0, len(META_TABLE_ID)):
        metaData = getMetaData(workbook, i)
        rule_clauses = {}
        # init_data
        rule_clauses['RULE_CLAUSES'] = generateRuleClauseList(
            workbook, i + 7, metaData)
        # generateRule(metaData,True)
    # exportToFile(metaData['RULE_CODE'], json.dumps(rule_clauses))
