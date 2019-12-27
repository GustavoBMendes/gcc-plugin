#include "tree-pass.h"
#include "context.h"
#include "function.h"
#include "tree.h"
#include "tree-ssa-alias.h"
#include "internal-fn.h"
#include "is-a.h"
#include "predict.h"
#include "basic-block.h"
#include "gimple-expr.h"
#include "gimple.h"
#include "gimple-pretty-print.h"
#include "gimple-iterator.h"
#include "gimple-walk.h"
#include "rtl.h"
#include "calls.h"
#include "profile.h"

// We must assert that this plugin is GPL compatible
int plugin_is_GPL_compatible;

int BB_ONE_SUCC = 0;
int BB_TWO_SUCCS = 0;
int BB_GT2_SUCCS = 0;

int BB_ONE_PRED = 0;
int BB_TWO_PREDS = 0;
int BB_GT2_PREDS = 0;

int BB_ONE_SUCC_PRED = 0;
int BB_2SUCCS_1PRED = 0;
int BB_1SUCC_2PREDS = 0;
int BB_2SUCCS_2PREDS = 0;
int BB_GT2_PS = 0;

int bb_15insns = 0;
int bb_15_100insns = 0;
int bb_500insns = 0;

int n_arestas = 0;
int n_critical_e = 0;
int n_abnormal_e = 0;

double avg_n_insns = 0.0;
int total_bb = 0;
int total_insns = 0;

double avg_phi = 0.0;
int avg_args_phi = 0.0;
int total_phi_nodes = 0;
int n_args_phi = 0;
int bb_no_phi = 0;
int bb_0_3_phi = 0;
int bb_gt3_phi = 0;
int bb_argphi_5 = 0;
int bb_argphi_1_5 = 0;

int n_references = 0;
int n_add_var = 0;
int n_add_fn = 0;

int fn_args_4 = 0;
int call_int = 0;
int call_pointer = 0;
int pointer_arg = 0;