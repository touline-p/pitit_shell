#include "../../incs/parsing_incs/minishell_parsing.h"
#include "../../incs/parsing_incs/prototypes_parsing.h"
#include "../../incs/execution_incs/structures_execution.h"

#include "../../libft/libft.h"

t_return_status	get_lexed_str_token_lst_from_line(char *line, t_string_token **str_tok_pt)
{
	t_token			*simple_tok_lst;
	t_string_token	*str_token_lst;

	simple_tok_lst = token_lst_constructor(line);
	if (simple_tok_lst == NULL)
		return (FAILED_MALLOC);
	preserve_token_lst(simple_tok_lst);
	split_toklst_on_meta(simple_tok_lst);
	str_token_lst = token_lst_to_str_token(simple_tok_lst);
	del_space_token(str_token_lst);
	if (simple_tok_lst == NULL)
		return (FAILED_MALLOC);
	*str_tok_pt = str_token_lst;
	return (SUCCESS);
}

/*
void	tests_metachar_groupment()
{
	tests_meta_split(TMG_M("no metachar"), regroup_meta, NULL, B);
	tests_meta_split(TMG_M("||j;fk&<>()"), regroup_meta, NULL, B);
	tests_meta_split(TMG_M("||&&>><<"), regroup_meta, NULL, B);
	tests_meta_split(TMG_M("|||&&&>>><<<"), regroup_meta, NULL, B);
}

#define TMS_M(x) regroup_meta(TMG_M(x))

void	tests_metachar_split()
{
	tests_meta_split(TMS_M("a"), split_on_meta, "pipe et commande", B);
	tests_meta_split(TMS_M("echo bonjour | cat -e > outfile"), split_on_meta, "pipe et commande", B);

}

void	tests_preserves(void)
{
	t_token hy;
	hy.esec = SECURED;
	hy.next = NULL;
	hy.sign_char = 'h';
	hy.token = LETTER;
	test_display_secured(&hy);
	hy.esec = UNSECURED;
	test_display_unsecured(&hy);
	test_escaping("iescape:\\t: i don t ::\n");
	tests_double_quote();
	tests_simple_quote();
	tests("", preserve_token_lst, "chaine vide", B);
	tests("\\bonjour \" a t\"ous", preserve_token_lst,NULL, B);
}

t_token	*tests_get_next_emt()
{
	tests_meta_split(TMG_M("ihih"), get_next_emt, NULL, B);

	return (NULL);
}

void	launcher(char *str, char **env)
{
	t_token *token;

	printf("Pour %s \n", str);
	token = TLC(str);
	display_tokens(token);
	preserve_token_lst(token);
	printf("preservation\n");
	display_tokens(token);
	expand_dollars(token, env);
	printf("expansion\n");
	display_tokens(token);

	printf("identification\n");
	split_toklst_on_meta(token);
	display_tokens(token);
	printf("split on them\n");
	split_on_meta(token);
	display_tokens(token);
	token_lst_clear(token);
}

void	tests_str_to_split_token(char **env)
{
	launcher("", env);
	launcher("bonjou\"r a t\"ous", env);
	launcher("bonjou\"r a $USER\" tous", env);
	launcher("bonjou\'r a $USER\' tous", env);
}

void	launcher_expand(char *str, char **env)
{
	(void)env;
	printf("for ->%s<-\n", str);
	t_token *tok = token_lst_constructor(str);
	display_tokens(tok);
	preserve_token_lst(tok);
	display_tokens(tok);
	expand_dollars(tok, env);
	display_tokens(tok);
	token_lst_clear(tok);
}

void	tests_expands(char **env)
{
	printf("first test\n");
	launcher_expand("", env);
	printf("second test\n");
	launcher_expand("bonjour a tous", env);
	printf("third test\n");
	launcher_expand("echo $USER", env);
	printf("fourth test\n");
	launcher_expand("echo $USR", env);
	printf("fifth test\n");
	launcher_expand("\"echo $USER\"", env);
	printf("sixth\n");
	launcher_expand("\'echo $USER\'", env);
}

char *_get_env_variable(t_token *token, char **env);

void	test_brick_expand_ln_get_env(char *search, char **env)
{
	t_token *tok = TLC(search);
	t_token *pin = tok->next;
	display_tokens(pin);
	char	*answer = _get_env_variable(tok, env);
	printf("i search %s i find %p\n", search, answer);
	if (answer)
		printf("%s\n", answer);
	token_lst_clear(tok);
}

#define TBEG(x) x,env

void	test_brick_expand_get_env(char **env)
{
	test_brick_expand_ln_get_env(TBEG("ceci"));
	test_brick_expand_ln_get_env(TBEG("user"));
	test_brick_expand_ln_get_env(TBEG("USER"));
	test_brick_expand_ln_get_env(TBEG("PATH"));
}

t_ert	_substitute_for_env_variable(t_token **last_token, char **env);
void	test_substitute_for_env_variable_ln(char *str, char **env)
{
	(void)env;
	t_token *tok = TLC(str);
	t_token *pin = tok;

	display_tokens(pin);
	_substitute_for_env_variable(&(tok), env);
	display_tokens(pin);
	token_lst_clear(tok);
}

void	test_substitute_for_env_variable(char **env)
{
	test_substitute_for_env_variable_ln(TBEG("$USER a chamger"));
	test_substitute_for_env_variable_ln(TBEG("$US\"ER\" a chamger"));
}

void	test_del_next_word_ln(char *str)
{
	t_token *tok = TLC(str);

	display_tokens(tok);
	del_next_word(tok);
	display_tokens(tok);
	token_lst_clear(tok);
}

void	test_del_next_word(void)
{
	test_del_next_word_ln("del this deviens this");
	test_del_next_word_ln("del\" \"  this deviens this");
}
void	test_insert_str_in_tkn_lst_ln(char *str, char *inserting, t_esec essec)
{
	t_token	*tok = TLC(str);

	display_tokens(tok);
	insert_str_in_tkn_lst(tok, inserting, essec);
	display_tokens(tok);
	token_lst_clear(tok);
}

void	test_insert_str_in_tkn_lst(void)
{
	test_insert_str_in_tkn_lst_ln("super liste", "j'ai une",SECURED);
}

void	test_brick_expand(char **env)
{
	(void)env;
	//test_brick_expand_get_env(env);
	//test_del_next_word();
	//test_insert_str_in_tkn_lst();

	test_substitute_for_env_variable(env);
}
void	suppress_quotes_ln(t_token *tok, char **env)
{
	(void)env;
	display_tokens(tok);
	preserve_token_lst(tok);
	display_tokens(tok);
	expand_dollars(tok, env);
	split_toklst_on_meta(tok);
	display_tokens(tok);
	display_tokens(tok);
	regroup_meta(tok);
	display_tokens(tok);
	split_on_meta(tok);
	display_tokens(tok);
	token_lst_clear(tok);
}

void	tokenisation_ln(char *str, char **env)
{
	t_token *tok;
	t_string_token *str_tok;
	t_instruction_block_tree *tree;
	tok = TLC(str);
	preserve_token_lst(tok);
	expand_dollars(tok, env);
	split_toklst_on_meta(tok);
	regroup_meta(tok);
	display_tokens(tok);
	str_tok = token_lst_to_str_token(tok);
	display_str_token(str_tok);
	if (str_tok == NULL)
		return ;
	//str_token_to_instruction_block_tree_on(str_tok, &tree);
	tree = NULL;
	display_instruction_block_tree(tree, 0);
	instruction_block_tree_destructor(tree);
}

void	tests_tokenisation(char **env)
{
	tokenisation_ln("echo damn $USER", env);
}

void	tests_tok_to_str_tok_ln(char *str, char **env)
{
	t_token			*tok;
	t_string_token	*str_tok;

	printf("\nfor ->%s<-\n", str);
	tok = TLC(str);
	preserve_token_lst(tok);
	expand_dollars(tok, env);
	split_toklst_on_meta(tok);
	regroup_meta(tok);
	display_tokens(tok);
	str_tok = token_lst_to_str_token(tok);
	if (str_tok != NULL)
	{
		del_space_token(str_tok);
		display_str_token(str_tok);
		string_token_destructor(str_tok);
	}
}

t_string_token	*parsing_constructor(char *str, char **env)
{
	t_token			*tok;
	t_string_token	*str_tok;

	tok = token_lst_constructor(str);
	preserve_token_lst(tok);
	expand_dollars(tok, env);
	split_toklst_on_meta(tok);
	regroup_meta(tok);
	str_tok = token_lst_to_str_token(tok);
	del_space_token(str_tok);
	display_str_token(str_tok);
	return (str_tok);
}

void	tests_tok_to_str_tok(char **env)
{
	tests_tok_to_str_tok_ln("", env);
	tests_tok_to_str_tok_ln("bonjour a tous", env);
	tests_tok_to_str_tok_ln("echo hi | cat > outfile", env);

}

void	tests_pipe_arr_ln(char *str, char **env)
{
	t_token			*tok;
	t_string_token	*str_tok;
	int 			**pipe_arr;

	printf("pipes arr for ->%s<-\n", str);
	tok = TLC(str);
	preserve_token_lst(tok);
	expand_dollars(tok, env);
	split_toklst_on_meta(tok);
	regroup_meta(tok);
	str_tok = token_lst_to_str_token(tok);
	if (init_pipe_arr_on(&pipe_arr, str_tok) != SUCCESS)
		printf("this_is_shitty\n");
	string_token_destructor(str_tok);
	ft_print_pipe_arr(pipe_arr);
	close_pipe_arr(pipe_arr);
	ft_free_int_arr(pipe_arr);
}

void	tests_pipe_arr(char **env)
{
	tests_pipe_arr_ln("", env);
	tests_pipe_arr_ln("echo bonjour | cat -e | grep bonjour > la", env);
	tests_pipe_arr_ln("| || | ||", env);
	tests_pipe_arr_ln(" bonjour a tous", env);
}

void	tests_all_first_child_ln(char *str, char **env)
{
	t_token *tok;
	t_string_token *str_tok;
	t_instruction_block_tree *first_child_block;
	int **pipe_arr;

	printf("->%s<-\n", str);
	tok = TLC(str);
	//display_tokens(tok);
	preserve_token_lst(tok);
	//display_tokens(tok);
	expand_dollars(tok, env);
	//display_tokens(tok);
	split_toklst_on_meta(tok);
	//display_tokens(tok);
	regroup_meta(tok);
	//display_tokens(tok);
	str_tok = token_lst_to_str_token(tok);
	//display_str_token(str_tok);
	del_space_token(str_tok);
	//display_str_token(str_tok);
	if (init_pipe_arr_on(&pipe_arr, str_tok) != SUCCESS)
		printf("this_is_shitty\n");
	t_string_token *cpy = str_tok;
	allocate_first_child_on(&cpy, &first_child_block, pipe_arr, env);
	string_token_destructor(str_tok);
	ft_print_pipe_arr(pipe_arr);
	close_pipe_arr(pipe_arr);
	ft_free_int_arr(pipe_arr);
	display_instruction_block_tree(first_child_block, 0);
	instruction_block_tree_destructor(first_child_block);
}

void	tests_all_first_child(char **env)
{
	tests_all_first_child_ln("", env);
	tests_all_first_child_ln("echo you \"\"| cat -e | then", env);
	tests_all_first_child_ln("echo you || cat -e | then", env);
	tests_all_first_child_ln("echo you & cat -e | then", env);
	tests_all_first_child_ln("echo you && cat -e | then", env);
	tests_all_first_child_ln("echo you < ah < uh < oh && cat -e | then | ", env);
	tests_all_first_child_ln("echo you > ah && cat -e | then | ", env);
}

int main(int ac, char **av, char **env) {

	(void)ac;
	(void)av;
	// (void)env;
	//tests_preserves();
	//tests_id_meta();
	//tests_metachar_groupment();
	//tests_metachar_split();
	//tests_get_next_emt();
	//test_brick_expand(env);
	//tests_expands(env);
	//tests_str_to_split_token(env);

	tests_tok_to_str_tok(env);
	//tests_pipe_arr(env);

	// tests_all_first_child(env);
	//tests_tokenisation(env);
	
	t_string_token	*str_tok = parsing_constructor(av[1], env);
	display_str_token(str_tok);
	
	return (0);
}
*/