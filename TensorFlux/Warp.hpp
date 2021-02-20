/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT license.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:
		using the methods from paper [6] to construct mesh with SMPL model; fit to 2D input pose
		S is both the set of all pixels ∋ {x ∈ silhouette}, and the binary function ∋ {S(x) = 1 if x ∈ Silhouette, S(x) = 0 if x ∉ Silhouette}
		project mesh into camera view to form silhouette mask Sₛₘₚₗ
		-> projection also yields Sₛₘₚₗ yields depth, normal, and skinning maps for pixels x ∈ Sₛₘₚₗ
											Zₛₘₚₗ(x), Nₛₘₚₗ(x), and Wₛₘₚₗ(x) respectively


		Skinning Map: Wₛₘₚₗ(x) is derived from per-vertex skinning weights, vector valued at each pixel, one skinning/weight per bone
		
		using Sₛₘₚₗ and input photo's silhouette mask S, warp Zₛₘₚₗ(x), Nₛₘₚₗ(x), and Wₛₘₚₗ(x) to construct
		Z_∂S(x) is the ouput depth map (at the silhouette only) x ∈ ∂S
		N(x)
		W(x)

		integrate over N(x) to recover the final depth map Z(x)

		in concrete terms:
		solve for smooth inverse warp, f(x), such that:
				S(x)	= Sₛₘₚₗ(f(x))
		Z_∂S(x ∈ ∂S)	= Zₛₘₚₗ(f(x))
				N(x)	= Nₛₘₚₗ(f(x))
				Z(x)	= ∫ N {x ∈ Z_∂S}
				W(x)	= Wₛₘₚₗ(f(x))

		In particular, following [5], we solve a sparse linear system to produce a Z(x) that agrees closely
		with the warped normals N(x) subject to the boundary constraint that Z(x) = Z∂S(x) for pixels x ∈ ∂S.

	[6] F. Bogo, A. Kanazawa, C. Lassner, P. Gehler, J. Romero,
		and M. J. Black. Keep it SMPL: Automatic estimation of 3D
		human pose and shape from a single image. In Computer
		Vision – ECCV 2016, Lecture Notes in Computer Science.
		Springer International Publishing, Oct. 2016. 2, 3, 8


Note: 1812.06162 An Emperical Model of Large-Batch Training summary: critical batch size B_crit can be predicted at the order of magnitude level
by measuring the gradient noise scale, most easily in the simplified form B_simple from equation 2.9


\**********************************************************************************************************************************************/


// S(x) =	{ 1, x inside  silhouette
//			{ 0, x outside silhouette


// so f(x) = S_smpl^-1(S(x)) iff S_smpl is invertible and S_smpl(f(x)) = S(x)
// S_smpl is invertible iff S_smpl is bijective, surjective, and injective
// S_smpl is surjective, because for every x in the sihouette, x = 1, and x = 0 for any other x by definition
// S_smpl is NOT injective, because x = 1 or x = 0, for every x, and there is no restriction of only one such x for each unique value
// S_smpl thus is not bijective, and can't be invertible, so solving for it f(x) requires another approach
// Wrong: S(x) is 1 or 0; must read the SMPL paper to see what the transform is doing to generate S_smpl

// Stochastic Gradient Descent






