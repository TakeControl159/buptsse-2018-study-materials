Victor=['Bertha', 'Amy', 'Diane', 'Erika', 'Clare']
Wyatt=['Diane', 'Bertha', 'Amy', 'Clare', 'Erika']
Xavier=['Bertha', 'Erika', 'Clare', 'Diane', 'Amy']
Yancey=['Amy', 'Diane', 'Clare', 'Bertha', 'Erika']
Zeus=['Bertha', 'Diane', 'Amy', 'Erika', 'Clare']
Men=[['Victor', Victor, False], ['Wyatt', Wyatt, False], ['Xavier', Xavier, False], ['Yancey', Yancey, False], ['Zeus', Zeus, False]]

Amy=['Zeus', 'Victor', 'Wyatt', 'Yancey', 'Xavier']
Bertha=['Xavier', 'Wyatt', 'Yancey', 'Victor', 'Zeus']
Clare=['Wyatt', 'Xavier', 'Yancey', 'Zeus', 'Victor']
Diane=['Victor', 'Zeus', 'Yancey', 'Xavier', 'Wyatt']
Erika=['Yancey', 'Wyatt', 'Zeus', 'Xavier', 'Victor']
Women=[['Amy', Amy, False], ['Bertha', Bertha, False], ['Clare', Clare, False], ['Diane', Diane, False], ['Erika', Erika, False]]

match=[]

def marriage_status(Men, Women):
    status=True
    for i in Men:
        status=status&i[2]

    for i in Women:
        status=status&i[2]

    return status

def look_up(Women, name):
    l=len(Women)
    for i in range(l):
        if name==Women[i][0]:
            return i
    return -1

def choose_WHO(l, cur_name,name):
    if l.index(cur_name)<l.index(name):
        return True
    else: return False

def calculate():
    while marriage_status(Men, Women)==False:
        for m in Men:
            #遍历每个男性
            if m[2]==False:
                #如果
                girls_num=len(Women)
                for n in range(girls_num):
                    if m[2]==False:
                        name=m[1][n]
                        location=look_up(Women, name)
                        #返回女生的位置
                        if Women[location][2]==False:
                        #如果这个女生没有结婚
                            match.extend([[name, m[0]]])
                            #将此组加入到匹配数组
                            m[2]=True
                            Women[location][2]=True
                        elif  Women[location][2]==True:
                            location2=look_up(match, name)
                            if choose_WHO(Women[location][1], m[0], match[location2][1]) ==True:
                                location3=look_up(Men, match[location2][1])
                                Men[location3][2]=False
                                match[location2]=[name, m[0]]
                                m[2]=True
                            else: continue
            else:continue

calculate()
print(match)










