#include <iostream>

#include "gcc-plugin.h"
#include "plugin-version.h"

#include "plugin.h"

static struct plugin_info my_gcc_plugin_info = { "1.0", "This is a plugin" };


namespace {
    

    const pass_data my_first_pass_data = 
    {
        GIMPLE_PASS,
        "my_first_pass",        /* name */
        OPTGROUP_NONE,          /* optinfo_flags */
        TV_NONE,                /* tv_id */
        PROP_gimple_any,        /* properties_required */
        0,                      /* properties_provided */
        0,                      /* properties_destroyed */
        0,                      /* todo_flags_start */
        0                       /* todo_flags_finish */
    };

    struct my_first_pass : gimple_opt_pass {

        my_first_pass(gcc::context *ctx)
            : gimple_opt_pass(my_first_pass_data, ctx)
        {
        }

        virtual unsigned int execute(function * fun) override {

            basic_block bb;
            int num_bb = 0, num_insns = 0;
            int n_direct_calls = 0, n_assign = 0;
            int n_cond_branches = 0, n_uncond_branches = 0;
            int int_type = 0, float_type = 0;
            int n_switch_insns = 0, n_unary_ops = 0;
            int pointer_arithmetic = 0;
            int lhs_int = 0, bin_op_1int = 0;
            int local_var_ref = 0, ref_local_var = 0;
            int ref_static_extern = 0, static_extern_ref = 0;
            int local_var_p = 0, static_extern_p = 0;
            int indirect_calls = 0;
            
            //percorre todos os basic-blocks(bb) de uma função fn
            FOR_ALL_BB_FN(bb, fun) {
                int inst = 0;
                int n_phi_nodes = 0;
                int bb_nargs_phi = 0;

                //gimple_bb_info *bb_info = &bb->il.gimple;
                num_bb += 1;
                total_bb += 1;

                //verifica se o bb possui apenas um sucessor
                if(single_succ_p(bb)) {

                    BB_ONE_SUCC += 1;

                    //um sucessor e um predecessor
                    if(single_pred_p(bb))
                        BB_ONE_SUCC_PRED += 1;
                }
                
                //numero de sucessor igual a 2
                else if(EDGE_COUNT(bb->succs) == 2) {

                    BB_TWO_SUCCS += 1;

                    //2 sucessores e 1 predecessor
                    if(single_pred_p(bb))
                        BB_2SUCCS_1PRED += 1;

                    //2 sucessores e 2 predecessores
                    else if(EDGE_COUNT(bb->preds) == 2)
                        BB_2SUCCS_2PREDS += 2;
                }

                //mais de 2 sucessores
                else if(EDGE_COUNT(bb->succs) > 2) {

                    BB_GT2_SUCCS += 1;

                    //mais de 2 sucessores e mais de 2 predecessores
                    if(EDGE_COUNT(bb->preds) > 2)
                        BB_GT2_PS += 1;
                }
                
                //único predecessor
                if(single_pred_p(bb))
                    BB_ONE_PRED += 1;

                //2 predecessores
                else if(EDGE_COUNT(bb->preds) == 2) {

                    BB_TWO_PREDS += 1;

                    //2 predecessores e 1 sucessor
                    if(single_succ_p(bb))
                        BB_1SUCC_2PREDS += 1;
                }

                //mais de 2 predecessores
                else if(EDGE_COUNT(bb->preds) > 2)
                    BB_GT2_PREDS += 1;


                if(bb->index == 0)  //entrada da função
                {
                    std::cerr << "ENTRY: "
                            << function_name(fun) << "\n"
                            << (LOCATION_FILE(fun->function_start_locus) ? : "<unknown>")
                            << ":" << LOCATION_LINE(fun->function_start_locus);
                }

                else if(bb->index == 1) //fim da função
                {
                    std::cerr << "\nNúmero de:\n";
                    std::cerr << "#1 - Basic Blocks nesta função: " 
                              << num_bb << "\n"; 
                    std::cerr << "#19 - Chamadas diretas nesta função: " 
                              << n_direct_calls << "\n";
                    std::cerr << "#20 - Desvios condicionais nesta função: " 
                              << n_cond_branches << "\n";
                    std::cerr << "#21 - Atribuições nesta função: " 
                              << n_assign << "\n"; 
                    std::cerr << "#22 - Desvios incondicionais nesta função: " 
                              << n_uncond_branches << "\n";
                    std::cerr << "#23 - Operações binárias inteiras nesta função: " 
                              << int_type << "\n";
                    std::cerr << "#24 - Operações binárias em ponto flutuante nesta função: " 
                              << float_type << "\n";
                    std::cerr << "#25 - Instruções nesta função: " 
                              << num_insns << "\n"; 
                    std::cerr << "#34 - Instruções switch nesta função: " 
                              << n_switch_insns << "\n"; 
                    std::cerr << "#35 - Operações unárias nesta função: " 
                              << n_unary_ops << "\n";
                    std::cerr << "#36 - Instruções aritméticas utilizando ponteiro nesta função: " 
                              << pointer_arithmetic << "\n";
                    std::cerr << "#40 - Chamadas indiretas nesta função: "
                              << indirect_calls << "\n";
                    std::cerr << "#41 - Operações de atribuição "
                              << "em que o operador do lado esquerdo da atribuição é inteiro: " 
                              << lhs_int << "\n";
                    std::cerr << "#42 - Operações binárias com pelo menos um operador como inteiro: " 
                              << bin_op_1int << "\n";
                    std::cerr << "#51 - Referencias a variáveis locais nesta função: " 
                              << ref_local_var << "\n";
                    std::cerr << "#52 - Referencias a variáveis 'static/extern' nesta função: " 
                              << ref_static_extern << "\n";
                    std::cerr << "#53 - Variáveis locais referenciadas nesta função: " 
                              << local_var_ref << "\n";
                    std::cerr << "#54 - Variáveis 'static/extern' referenciadas nesta função: " 
                              << static_extern_ref << "\n";
                    std::cerr << "#55 - Variáveis locais do tipo pointer nesta função: " 
                              << static_extern_ref << "\n";
                    std::cerr << "#56 - Variáveis 'static/extern' do tipo pointer nesta função: " 
                              << static_extern_ref << "\n";
                    std::cerr << "EXIT: "
                            << function_name(fun) << "\n"
                            << (LOCATION_FILE(fun->function_end_locus) ? : "<unknown>") <<
                            ":" << LOCATION_LINE(fun->function_end_locus);
                }
                else
                {
                    //iterator para phi node
                    gphi_iterator i;
                    for(i = gsi_start_phis(bb); !gsi_end_p(i); gsi_next(&i)) {

                        gphi *phi = i.phi();
                        n_phi_nodes += 1;   //numero de phi nodes neste basic block, variavel local
                        total_phi_nodes += 1;   //total phi nodes para todos BBs, variavel global
                        n_args_phi += static_cast<int>(gimple_phi_num_args(phi));   //nro args para todos BBs
                        bb_nargs_phi += static_cast<int>(gimple_phi_num_args(phi)); //nro args para este BB
                    }
                    
                    //nenhum phi node no bb
                    if(n_phi_nodes == 0)
                        bb_no_phi += 1;

                    //entre 1 e 3 phi nodes
                    else if(n_phi_nodes <= 3)
                        bb_0_3_phi += 1;

                    //mais que 3
                    else
                        bb_gt3_phi += 1;

                    //mais que 5 argumentos no phi node
                    if(bb_nargs_phi > 5)
                        bb_argphi_5 += 1;

                    //entre 1 e 5
                    else
                        if(bb_nargs_phi >= 1)
                            bb_argphi_1_5 += 1;

                    //iterator para um statement
                    gimple_stmt_iterator gsi;
                    for(gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi)) {

                        gimple* stmt = gsi_stmt(gsi);
                        
                        num_insns += 1;     //numero de instruções nesta função
                        inst += 1;          //numero de instruções no bb
                        total_insns += 1;   //numero total de instruções no código, var global

                        //intrução que faz referencia a memória
                        if(gimple_references_memory_p(stmt))
                            n_references += 1;
                        //acesso ao endereço de memoria da variavel
                        if(gimple_has_mem_ops(stmt))
                            n_add_var += 1;

                        switch(gimple_code(stmt)) {

                            case GIMPLE_CALL:
                            {
                                
                                n_direct_calls += 1;

                                //função que possui ponteiro como argumento
                                if(gimple_has_mem_ops(stmt))
                                    n_add_fn += 1;
                                
                                //numero de argumento da função maior que 4
                                if(gimple_call_num_args(stmt) > 4)
                                    fn_args_4 += 1;

                                tree lhs = gimple_call_lhs(stmt);
                                tree rhs = gimple_call_fn(stmt);
                                //variavel local referenciada
                                if(lhs != NULL) {
                                    if(!is_global_var(lhs))
                                        local_var_ref += 1;
                                    else
                                        static_extern_ref += 1;
                                }

                                //chamada indireta de uma função
                                if(rhs != NULL) {
                                    if(TREE_CODE(TREE_TYPE(rhs)) == POINTER_TYPE)
                                        indirect_calls += 1;
                                }

                                const gcall *call_stmt = as_a <const gcall *> (stmt);
                                tree call_type = gimple_call_return_type(call_stmt);
                                //retorno do tipo inteiro
                                if(TREE_CODE(call_type) == INTEGER_TYPE)
                                    call_int += 1;
                                else
                                    //tipo ponteiro
                                    if(TREE_CODE(call_type) == POINTER_TYPE)
                                        call_pointer += 1;

                                unsigned int index = 1;
                                while(gimple_num_ops(call_stmt) > index + 3) {

                                    if(TREE_CODE(TREE_TYPE(call_stmt->op[index+3])) 
                                    == POINTER_TYPE)
                                        pointer_arg += 1;
                                    index += 1;
                                }

                                break;
                            }

                            case GIMPLE_ASSIGN:
                            {
                                n_assign += 1;

                                tree rhs1 = gimple_assign_rhs1(stmt);
                                tree rhs3 = gimple_assign_rhs2(stmt);
                                tree lhs1 = gimple_assign_lhs(stmt);

                                //referencia para variavel local
                                if(!is_global_var(lhs1)) {
                                    ref_local_var += 1;
                                    if(TREE_CODE(TREE_TYPE(lhs1)) == POINTER_TYPE)
                                        local_var_p += 1;
                                }
                                else {
                                    ref_static_extern += 1;
                                    if(TREE_CODE(TREE_TYPE(lhs1)) == POINTER_TYPE)
                                        static_extern_p += 1;
                                }

                                if(TREE_CODE(TREE_TYPE(lhs1)) == INTEGER_TYPE)
                                    lhs_int += 1;

                                if(rhs3 != NULL)
                                {
                                    if(TREE_CODE(TREE_TYPE(rhs1)) == INTEGER_TYPE) 
                                        if(TREE_CODE(TREE_TYPE(rhs3)) == INTEGER_TYPE)
                                            int_type += 1;
                                        else
                                            bin_op_1int += 1;

                                    else if(TREE_CODE(TREE_TYPE(rhs3)) == INTEGER_TYPE)
                                        bin_op_1int += 1;

                                    else
                                        if(TREE_CODE(TREE_TYPE(rhs1)) == REAL_TYPE 
                                        && TREE_CODE(TREE_TYPE(rhs3)) == REAL_TYPE)
                                            float_type += 1;

                                    if(TREE_CODE(TREE_TYPE(rhs1)) == POINTER_TYPE
                                    && TREE_CODE(TREE_TYPE(rhs3)) == POINTER_TYPE)
                                        pointer_arithmetic += 1;
                                }

                                if(gimple_num_ops(stmt) == 2)
                                    n_unary_ops += 1;

                                break;
                            }
                            
                            //instruções do tipo condicional
                            case GIMPLE_COND:
                            {
                                n_cond_branches += 1;
                            }

                            //desvio incondicional
                            case GIMPLE_GOTO:
                            {
                                n_uncond_branches += 1;
                            }

                            //inst tipo switch
                            case GIMPLE_SWITCH:
                            {
                                n_switch_insns += 1;
                            }

                            default:
                                break;
                        }
                    }

                    if(inst < 15)
                            bb_15insns += 1;
                    else if(inst < 100)
                        bb_15_100insns += 1;
                    else
                        if(inst > 500)
                            bb_500insns += 1;
                }

                edge e;
                edge_iterator ei;

                FOR_EACH_EDGE(e, ei, bb->succs) {

                    n_arestas += 1;

                    if(EDGE_CRITICAL_P(e))
                        n_critical_e += 1;
                    if(e->flags & EDGE_ABNORMAL)
                        n_abnormal_e += 1;
                }

            }

            std::cerr << "\n\n";

            return 0;
        }

        virtual my_first_pass* clone() override {
            return this;
        }
    };
}

namespace {

    void start_graph() {

        std::cerr << "Árvore AST \n{\n";
    }

    void end_graph() {

        std::cerr << "\n}\n";
    }

    void finish_gcc(void *gcc_data, void *user_data) {

        std::cerr << "Número total de basic blocks com:\n";
        std::cerr << "#2 - Exatamente 1 sucessor: " 
                  << BB_ONE_SUCC << "\n";
        std::cerr << "#3 - Exatamente 2 sucessores: " 
                  << BB_TWO_SUCCS << "\n";
        std::cerr << "#4 - Mais de 2 sucessores: " 
                  << BB_GT2_SUCCS << "\n";
        std::cerr << "#5 - Um único predecessor: " 
                  << BB_ONE_PRED << "\n";
        std::cerr << "#6 - Exatamente 2 predecessores: " 
                  << BB_TWO_PREDS << "\n";
        std::cerr << "#7 - Mais de 2 predecessores: " 
                  << BB_GT2_PREDS << "\n";
        std::cerr << "#8 - Único sucessor e predecessor: " 
                  << BB_ONE_SUCC_PRED << "\n";
        std::cerr << "#9 - Único predecessor e dois sucessores: " 
                  << BB_ONE_SUCC_PRED << "\n";
        std::cerr << "#10 - Único sucessor e dois predecessores: "
                  << BB_1SUCC_2PREDS << "\n";
        std::cerr << "#11 - Dois sucessores e dois predecessores: "
                  << BB_2SUCCS_2PREDS << "\n";
        std::cerr << "#12 - Mais de dois sucessores e predecessores: "
                  << BB_2SUCCS_2PREDS << "\n";
        std::cerr << "#13 - Menos de 15 instruções: "
                  << bb_15insns << "\n";
        std::cerr << "#14 - Entre 15 e 100 instruções: "
                  << bb_15_100insns << "\n";
        std::cerr << "#15 - Mais de 500 instruções: "
                  << bb_500insns << "\n";

        std::cerr << "\nNúmero total de: " << "\n";
        std::cerr << "#16 - Arestas na árvore de fluxo: "
                  << n_arestas << "\n";
        std::cerr << "#17 - Arestas críticas na árvore de fluxo: "
                  << n_critical_e << "\n";
        std::cerr << "#18 - 'Abnormal edges' na árvore de fluxo: "
                  << n_abnormal_e << "\n";
        
        avg_n_insns = total_insns / total_bb;
        std::cerr << "\n#26 - Número médio de instruções por basic blocks: "
                  << avg_n_insns << "\n";
        avg_phi = total_phi_nodes / total_bb;
        std::cerr << "#27 - Número médio de phi nodes por basic blocks: "
                  << avg_phi << "\n";
        //avg_args_phi = n_args_phi / total_phi_nodes;
        std::cerr << "#28 - Número médio de argumentos por phi nodes: "
                  << avg_args_phi << "\n";
        std::cerr << "\nNúmero total de basic blocks: \n";
        std::cerr << "#29 - Sem phi nodes: "
                  << bb_no_phi << "\n";
        std::cerr << "#30 - Que possuem entre 0 e 3 phi nodes: "
                  << bb_0_3_phi << "\n";
        std::cerr << "#31 - Que possuem mais de 3 phi nodes: "
                  << bb_gt3_phi << "\n";
        std::cerr << "#32 - Que possuem mais de 5 argumentos no total contando todos os phi nodes: "
                  << bb_argphi_5 << "\n";
        std::cerr << "#33 - Que possuem entre 1 e 5 argumentos no total de todos seus phi nodes: "
                  << bb_argphi_1_5 << "\n";

        std::cerr << "\n#37 - Número de referencias via ponteiro: "
                  << n_references << "\n";
        std::cerr << "\n#38 - Número de vezes em que o endereço de uma variável foi acessado: "
                  << n_add_var << "\n";
        std::cerr << "\n#39 - Número de vezes em que o endereço de uma função foi acessado: "
                  << n_add_fn << "\n";
        std::cerr << "\n#43 - Número de funções que possuem argumentos do tipo pointer: "
                  << pointer_arg << "\n";
        std::cerr << "\n#44 - Número de funções com mais de 4 argumentos: "
                  << fn_args_4 << "\n";
        std::cerr << "\n#45 - Número de funções que retornam tipo pointer: "
                  << call_pointer << "\n";
        std::cerr << "\n#46 - Número de funções que retornam tipo inteiro: "
                  << call_int << "\n";

        end_graph();
    }

}

int plugin_init (struct plugin_name_args *plugin_info,
		         struct plugin_gcc_version *version){
	
	if (!plugin_default_version_check (version, &gcc_version)){
        std::cerr << "This GCC plugin is for version " 
                  << GCCPLUGIN_VERSION_MAJOR << "." 
                  << GCCPLUGIN_VERSION_MINOR << "\n";
		return 1;
    }

    std::cerr << "Plugin info\n";
	std::cerr << "===========\n\n";
	std::cerr << "Nome Plugin: " << plugin_info->base_name << "\n";
	std::cerr << "Nome executável: " << plugin_info->full_name << "\n";
	std::cerr << "Número de argumentos deste plugin: " << plugin_info->argc << "\n";

	std::cerr << "\n";
    std::cerr << "Informações da versão\n";
    std::cerr << "============\n\n";
    std::cerr << "Versão base: " << version->basever << "\n";
    std::cerr << "Date stamp: " << version->datestamp << "\n";
    std::cerr << "Configurações: " << version->configuration_arguments << "\n";
    std::cerr << "\n";

    std::cerr << "Plugin inicializado!\n\n";

    register_callback(plugin_info->base_name, PLUGIN_INFO,
                    NULL, &my_gcc_plugin_info);

    struct register_pass_info pass_info;

    pass_info.pass = new my_first_pass(g);
    pass_info.reference_pass_name = "cfg";
    pass_info.ref_pass_instance_number = 1;
    pass_info.pos_op = PASS_POS_INSERT_AFTER;

    register_callback (plugin_info->base_name, 
                        PLUGIN_PASS_MANAGER_SETUP, 
                        NULL, &pass_info);

    register_callback(plugin_info->base_name, PLUGIN_FINISH, finish_gcc, NULL);

    start_graph();

    return 0;
}
