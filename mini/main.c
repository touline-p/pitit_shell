/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoumeau <bpoumeau@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:33:30 by bpoumeau          #+#    #+#             */
/*   Updated: 2023/03/12 00:43:24 by bpoumeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define S SILENCIEUX
#define B BAVARD

#ifndef SILENCIEUX
# define SILENCIEUX true
#endif
#define BAVARD false

#include <stdio.h>
#include "test_mini.h"
#include "mini_parsing.h"

void	test1()
{
	printf("when \"\"\n");
	t_token *tok = token_lst_constructor(ft_strdup(""));
	display_tokens(tok);
	token_lst_clear(tok);
}

void	test_line(char *str)
{
	printf("when ->%s<-\n", str);
	t_token	*tok = token_lst_constructor(str);
	display_tokens(tok);
	token_lst_clear(tok);
}

void	test_lexing(char *str)
{
	printf("when ->%s<-\nlexed :\n", str);
	t_token *tok = token_lst_constructor(str);
	//t_lexed	*lex = lexor(tok);
	(void)tok;
}

void	test_display_secured(t_token *tok)
{
	printf("test secured ->\\h<-\n");
	display_tokens(tok);
}
void	test_display_unsecured(t_token *hy)
{
	printf("test unsecured ->h<-\n");
	display_tokens(hy);
}

t_ert 	test_squote_launcher(t_token *tok)
{
	while (tok->token != EOL)
	{
		if (tok->sign_char == '\''
			&& squoting_process(NULL, tok, &tok) != SUCCESS)
			return (FAILURE);
		tok = tok->next;
	}
	return (SUCCESS);
}

t_ert	dquoting_process(t_token *last_token, t_token *token, t_token **end_of_quot_pt);
t_ert 	test_double_quote_launcher(t_token *tok)
{
	dquoting_process(tok, tok->next, &tok);
	return (SUCCESS);
}

void	tests(char *str, t_ert(*launcher)(t_token *), char *msg, bool silence)
{
	if (silence)
		return;
	printf("\n");
	if (msg)
		printf("%s\n", msg);
	printf("pour ->%s<-\n", str);
	t_token *tok = token_lst_constructor(str);
	if (launcher(tok) == SUCCESS)
		display_tokens(tok);
	token_lst_clear(tok);

}
void	tests_double_quote(void)
{
	tests("\"test", test_double_quote_launcher, "erreure ligne non terminee", B);
	tests("\"test\"", test_double_quote_launcher, "cas normale les char entre quotes sont preserve mais pas les quotes", B);
	tests("\"t\\e\\\"st\"", test_double_quote_launcher, "slash avant la double quote doit preserver puis partir", B);
	tests("\"$\"", test_double_quote_launcher, "le $ ne peut pas etre preserve par les double quote", B);
}

void	tests_simple_quote(void)
{
	tests("\'test\'", test_squote_launcher, "cas normal les char entre quotes sont preserve mais pas les quotes", B);
	tests("\'test", test_squote_launcher, "cas normal les char entre quotes sont preserve mais pas les quotes", B);
	tests("\'\'te\'st\'", test_squote_launcher, "seul les char entre quotes sont preserve", B);
	tests("\'te\'st", test_squote_launcher, "seul les char entre quotes sont preserve", B);
}

void	test_escaping(char *str)
{
	printf("all chars after\\ must be protected\n->%s<-\n", str);
	str = ft_strdup(str);
	t_token *tok = token_lst_constructor(str);
	escaping_chars(tok);
	display_tokens(tok);
	token_lst_clear(tok);
}

void	tests_meta_split(t_token *token_lst, t_token*(*launcher)(t_token *), char *msg, bool silence)
{
	t_token *mem;

	mem = token_lst;
	if (silence)
		return (token_lst_clear(mem));
	if (msg)
		printf("%s\n", msg);
	printf("\npour\n");
	display_tokens(token_lst);
	launcher(token_lst);
	display_tokens(token_lst);
	token_lst_clear(mem);
	printf("\n");
}

#define TLC(x) token_lst_constructor(x)

void	tests_id_meta(void)
{
	tests_meta_split(TLC("no metachar"), split_toklst_on_meta, NULL, B);
	tests_meta_split(TLC("just a | metachar"),split_toklst_on_meta, NULL, B);
	tests_meta_split(TLC("just a & metachar"),split_toklst_on_meta, NULL, B);
	tests_meta_split(TLC("just a ( metachar"),split_toklst_on_meta, NULL, B);
	tests_meta_split(TLC("just a ) metachar"),split_toklst_on_meta, NULL, B);
	tests_meta_split(TLC(""),split_toklst_on_meta, "nothing", B);
	tests_meta_split(TLC("||j;fk&<>()"),split_toklst_on_meta, "Only metachar", B);
}

#define TMG_M(x) split_toklst_on_meta(TLC(x))

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
	/*t_token hy;
	hy.esec = SECURED;
	hy.next = NULL;
	hy.sign_char = 'h';
	hy.token = LETTER;
	test_display_secured(&hy);
	hy.esec = UNSECURED;
	test_display_unsecured(&hy);
	test_escaping("iescape:\\t: i don t ::\n");*/
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
		display_str_token(str_tok);
		string_token_destructor(str_tok);
	}
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
	//tests_preserves();
	//tests_id_meta();
	//tests_metachar_groupment();
	//tests_metachar_split();
	//tests_get_next_emt();
	//test_brick_expand(env);
	//tests_expands(env);
	//tests_str_to_split_token(env);

	//tests_tok_to_str_tok(env);
	//tests_pipe_arr(env);

	tests_all_first_child(env);
	//tests_tokenisation(env);
	return (0);
}
