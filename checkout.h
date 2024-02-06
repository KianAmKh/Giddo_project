#ifndef checkout_h
#define checkout_h
int checkout(int commit_id);
int submit_checkout(int commit_id);
int checkout_branch(char *branch_name);
int checkout_head();
#endif