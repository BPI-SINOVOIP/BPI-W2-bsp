/* Generated automatically by the program 'build/genpreds'
   from the machine description file '/ssd/shunyen/sdk-4.9/gcc/gcc/config/aarch64/aarch64.md'.  */

#ifndef GCC_TM_PREDS_H
#define GCC_TM_PREDS_H

#ifdef HAVE_MACHINE_MODES
extern int general_operand (rtx, enum machine_mode);
extern int address_operand (rtx, enum machine_mode);
extern int register_operand (rtx, enum machine_mode);
extern int pmode_register_operand (rtx, enum machine_mode);
extern int scratch_operand (rtx, enum machine_mode);
extern int immediate_operand (rtx, enum machine_mode);
extern int const_int_operand (rtx, enum machine_mode);
extern int const_double_operand (rtx, enum machine_mode);
extern int nonimmediate_operand (rtx, enum machine_mode);
extern int nonmemory_operand (rtx, enum machine_mode);
extern int push_operand (rtx, enum machine_mode);
extern int pop_operand (rtx, enum machine_mode);
extern int memory_operand (rtx, enum machine_mode);
extern int indirect_operand (rtx, enum machine_mode);
extern int ordered_comparison_operator (rtx, enum machine_mode);
extern int comparison_operator (rtx, enum machine_mode);
extern int cc_register (rtx, enum machine_mode);
extern int aarch64_call_insn_operand (rtx, enum machine_mode);
extern int aarch64_simd_register (rtx, enum machine_mode);
extern int aarch64_reg_or_zero (rtx, enum machine_mode);
extern int aarch64_reg_or_fp_zero (rtx, enum machine_mode);
extern int aarch64_reg_zero_or_m1_or_1 (rtx, enum machine_mode);
extern int aarch64_fp_compare_operand (rtx, enum machine_mode);
extern int aarch64_plus_immediate (rtx, enum machine_mode);
extern int aarch64_plus_operand (rtx, enum machine_mode);
extern int aarch64_pluslong_immediate (rtx, enum machine_mode);
extern int aarch64_pluslong_operand (rtx, enum machine_mode);
extern int aarch64_logical_immediate (rtx, enum machine_mode);
extern int aarch64_logical_operand (rtx, enum machine_mode);
extern int aarch64_shift_imm_si (rtx, enum machine_mode);
extern int aarch64_shift_imm_di (rtx, enum machine_mode);
extern int aarch64_shift_imm64_di (rtx, enum machine_mode);
extern int aarch64_reg_or_shift_imm_si (rtx, enum machine_mode);
extern int aarch64_reg_or_shift_imm_di (rtx, enum machine_mode);
extern int aarch64_imm3 (rtx, enum machine_mode);
extern int aarch64_pwr_imm3 (rtx, enum machine_mode);
extern int aarch64_pwr_2_si (rtx, enum machine_mode);
extern int aarch64_pwr_2_di (rtx, enum machine_mode);
extern int aarch64_mem_pair_offset (rtx, enum machine_mode);
extern int aarch64_mem_pair_operand (rtx, enum machine_mode);
extern int aarch64_valid_symref (rtx, enum machine_mode);
extern int aarch64_tls_ie_symref (rtx, enum machine_mode);
extern int aarch64_tls_le_symref (rtx, enum machine_mode);
extern int aarch64_mov_operand (rtx, enum machine_mode);
extern int aarch64_movti_operand (rtx, enum machine_mode);
extern int aarch64_reg_or_imm (rtx, enum machine_mode);
extern int aarch64_comparison_operator (rtx, enum machine_mode);
extern int aarch64_comparison_operation (rtx, enum machine_mode);
extern int aarch64_sync_memory_operand (rtx, enum machine_mode);
extern int vect_par_cnst_hi_half (rtx, enum machine_mode);
extern int vect_par_cnst_lo_half (rtx, enum machine_mode);
extern int aarch64_simd_lshift_imm (rtx, enum machine_mode);
extern int aarch64_simd_rshift_imm (rtx, enum machine_mode);
extern int aarch64_simd_reg_or_zero (rtx, enum machine_mode);
extern int aarch64_simd_struct_operand (rtx, enum machine_mode);
extern int aarch64_simd_general_operand (rtx, enum machine_mode);
extern int aarch64_simd_nonimmediate_operand (rtx, enum machine_mode);
extern int aarch64_simd_imm_zero (rtx, enum machine_mode);
extern int aarch64_simd_imm_minus_one (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_qi (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_hi (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_si (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_di (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_offset_qi (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_offset_hi (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_offset_si (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_offset_di (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_bitsize_qi (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_bitsize_hi (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_bitsize_si (rtx, enum machine_mode);
extern int aarch64_simd_shift_imm_bitsize_di (rtx, enum machine_mode);
#endif /* HAVE_MACHINE_MODES */

#define CONSTRAINT_NUM_DEFINED_P 1
enum constraint_num
{
  CONSTRAINT__UNKNOWN = 0,
  CONSTRAINT_k,
  CONSTRAINT_Ucs,
  CONSTRAINT_w,
  CONSTRAINT_x,
  CONSTRAINT_I,
  CONSTRAINT_J,
  CONSTRAINT_K,
  CONSTRAINT_L,
  CONSTRAINT_M,
  CONSTRAINT_N,
  CONSTRAINT_S,
  CONSTRAINT_Y,
  CONSTRAINT_Z,
  CONSTRAINT_Ush,
  CONSTRAINT_Uss,
  CONSTRAINT_Usd,
  CONSTRAINT_Usf,
  CONSTRAINT_UsM,
  CONSTRAINT_Ui1,
  CONSTRAINT_Ui3,
  CONSTRAINT_Up3,
  CONSTRAINT_Q,
  CONSTRAINT_Ump,
  CONSTRAINT_Utv,
  CONSTRAINT_Ufc,
  CONSTRAINT_Dn,
  CONSTRAINT_Dh,
  CONSTRAINT_Dq,
  CONSTRAINT_Dl,
  CONSTRAINT_Dr,
  CONSTRAINT_Dz,
  CONSTRAINT_Dd,
  CONSTRAINT__LIMIT
};

extern enum constraint_num lookup_constraint (const char *);
extern bool constraint_satisfied_p (rtx, enum constraint_num);

static inline size_t
insn_constraint_len (char fc, const char *str ATTRIBUTE_UNUSED)
{
  switch (fc)
    {
    case 'D': return 2;
    case 'U': return 3;
    default: break;
    }
  return 1;
}

#define CONSTRAINT_LEN(c_,s_) insn_constraint_len (c_,s_)

extern enum reg_class regclass_for_constraint (enum constraint_num);
#define REG_CLASS_FROM_CONSTRAINT(c_,s_) \
    regclass_for_constraint (lookup_constraint (s_))
#define REG_CLASS_FOR_CONSTRAINT(x_) \
    regclass_for_constraint (x_)

extern bool insn_const_int_ok_for_constraint (HOST_WIDE_INT, enum constraint_num);
#define CONST_OK_FOR_CONSTRAINT_P(v_,c_,s_) \
    insn_const_int_ok_for_constraint (v_, lookup_constraint (s_))

#define CONST_DOUBLE_OK_FOR_CONSTRAINT_P(v_,c_,s_) 0

#define EXTRA_CONSTRAINT_STR(v_,c_,s_) \
    constraint_satisfied_p (v_, lookup_constraint (s_))

extern bool insn_extra_memory_constraint (enum constraint_num);
#define EXTRA_MEMORY_CONSTRAINT(c_,s_) insn_extra_memory_constraint (lookup_constraint (s_))

#define EXTRA_ADDRESS_CONSTRAINT(c_,s_) false

#endif /* tm-preds.h */
